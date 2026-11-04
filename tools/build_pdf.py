#!/usr/bin/env python3
"""一键生成手机阅读版及附全部raw原件版。要求Pandoc、XeLaTeX、中文字体、PyMuPDF。

只读取仓库内Markdown和源代码；不执行文档中的代码，也不从网络下载资料。
全部教学代码保持原文，长行仅在PDF排版时折行。宽表转为逐条卡片，方便手机阅读。
"""
from pathlib import Path
import argparse,hashlib,json,os,re,shutil,subprocess,sys,time,unicodedata
from urllib.parse import unquote

ROOT=Path(__file__).resolve().parents[1]
EXCLUDED={'build','dist','.git','.xmake','__pycache__'}
MOBILE='大一C语言全面指南_C99_CPP11_手机版.pdf'
COMPLETE='大一C语言全面指南_C99_CPP11_含全部原始资料.pdf'

def require(program):
    path=shutil.which(program)
    if not path:raise SystemExit(f'缺少{program}。请先按docs/19_build_pdf.md安装PDF依赖。')
    return path

def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def identifier(path):return 'file-'+hashlib.sha1(str(path.relative_to(ROOT)).encode()).hexdigest()[:16]
def text_inline(text):return [{'t':'Str','c':text}]
def para(text):return {'t':'Para','c':text_inline(text)}
def included(path):return not any(part in EXCLUDED for part in path.relative_to(ROOT).parts)

def collect():
    all_md={p for p in ROOT.rglob('*.md') if included(p)}
    ordered=[ROOT/'README.md']+sorted((ROOT/'docs').glob('*.md'))+[ROOT/'raw/README.md']
    ordered += [ROOT/'practice/README.md',ROOT/'practice/mock_exam.md',ROOT/'practice/mock_answers.md',ROOT/'practice/s3_solutions.md',ROOT/'practice/mistakes.md',ROOT/'labs/report_template.md']
    ordered += sorted((ROOT/'practice/tasks').glob('*.md'))
    ordered += sorted(all_md-set(ordered))
    docs=list(dict.fromkeys(p for p in ordered if p in all_md))
    code=[]
    for e in json.loads((ROOT/'data/examples.json').read_text()):
        code += [ROOT/f'src/c/{e["id"]}.c',ROOT/f'src/cpp/{e["id"]}.cpp']
    extra=sorted(p for p in ROOT.rglob('*') if p.is_file() and included(p) and (p.suffix in {'.py','.lua','.tex','.yml','.yaml'} or p.name in {'Makefile','.clang-format','requirements-pdf.txt'}) and p not in code)
    assert set(docs)==all_md
    assert set(code)=={p for p in (ROOT/'src').rglob('*') if p.suffix in {'.c','.cpp'}}
    return docs,code,extra

def flatten(blocks):
    result=[]
    for block in blocks:
        if block['t'] in {'Para','Plain','Header'}:
            if result:result.append({'t':'Space'})
            result+=block['c'][-1] if block['t']=='Header' else block['c']
        elif block['t']=='CodeBlock':result.append({'t':'Code','c':[['',[],[]],block['c'][1]]})
    return result or text_inline('—')

def table_cards(node):
    # Pandoc 3表格：每行仍保留全部字段，只把横排改成逐条阅读。
    attr,caption,spec,head,bodies,foot=node['c']
    headrows=head[1]
    headers=[flatten(cell[4]) for cell in headrows[-1][1]] if headrows else []
    rows=[]
    for body in bodies:rows+=body[2]+body[3]
    rows+=foot[1]
    items=[]
    for row in rows:
        cells=[flatten(cell[4]) for cell in row[1]]
        if not cells:continue
        content=[{'t':'Strong','c':cells[0]}]
        for i,cell in enumerate(cells[1:],1):
            content.append({'t':'LineBreak'})
            content += [{'t':'Strong','c':(headers[i] if i<len(headers) else text_inline(f'字段{i+1}'))+text_inline('：')}]+cell
        items.append([{'t':'Para','c':content}])
    return {'t':'BulletList','c':items}

def wrap_code(text,columns=42):
    # 先分成可分页的显示行，避免单条极长Python字符串在TeX中整块伸出页面。
    # 仅改变PDF布局；仓库源文件不修改。续行缩进4格。
    output=[]
    for line in text.expandtabs(4).splitlines():
        current='';width=0
        for char in line:
            size=2 if unicodedata.east_asian_width(char) in {'W','F','A'} else 1
            if width+size>columns:
                output.append(current);current='    ';width=4
            current+=char;width+=size
        output.append(current)
    return '\n'.join(output)

def breakable_latex(text,monospace=True):
    # 行内代码也允许折行；否则窄页中的长函数调用会伸出右边界。
    escapes={'\\':r'\textbackslash{}','{':r'\{','}':r'\}','$':r'\$','&':r'\&','#':r'\#','_':r'\_','%':r'\%','^':r'\textasciicircum{}','~':r'\textasciitilde{}',' ':r'\ '}
    body=''.join(escapes.get(char,char)+r'\allowbreak{}' for char in text)
    return {'t':'RawInline','c':['latex',(r'\texttt{' if monospace else '{')+body+'}']}

def walk(value,source,anchors):
    if isinstance(value,list):return [walk(x,source,anchors) for x in value]
    if not isinstance(value,dict):return value
    if value.get('t')=='Header':return value
    if value.get('t')=='CodeBlock':
        value['c'][1]=wrap_code(value['c'][1]);return value
    if value.get('t')=='Code':return breakable_latex(value['c'][1])
    if value.get('t')=='Str' and re.search(r'[A-Za-z0-9_./:-]{16,}',value['c']):
        parts=[];position=0
        for match in re.finditer(r'[A-Za-z0-9_./:-]{16,}',value['c']):
            if match.start()>position:parts+=text_inline(value['c'][position:match.start()])
            parts.append(breakable_latex(match[0]));position=match.end()
        if position<len(value['c']):parts+=text_inline(value['c'][position:])
        return {'t':'Span','c':[['',[],[]],parts]}
    if value.get('t')=='Table':return walk(table_cards(value),source,anchors)
    if value.get('t')=='Link':
        attr,label,destination=value['c'];target=destination[0]
        if not target.startswith(('http://','https://','mailto:')):
            filepart=unquote(target.split('#')[0])
            resolved=(source.parent/filepart).resolve() if filepart else source
            if resolved in anchors:return {'t':'Link','c':[attr,walk(label,source,anchors),['#'+anchors[resolved],'']]}
            # 本机路径不能在手机上直接打开。保留文字，原件由最后一部分提供。
            return {'t':'Span','c':[['',[],[]],walk(label,source,anchors)]}
    return {key:walk(item,source,anchors) for key,item in value.items()}

def add_document(path,pandoc,anchors,blocks,api):
    result=subprocess.run([pandoc,'--from=markdown','--to=json',str(path)],capture_output=True,text=True,check=True)
    document=json.loads(result.stdout);api[:]=document['pandoc-api-version'];content=document['blocks']
    blocks.append({'t':'RawBlock','c':['latex','\\clearpage']})
    first=True
    for block in content:
        if block['t']=='Header':
            level,attr,title=block['c']
            if first and level==1:
                attr[0]=anchors[path];first=False
            else:
                block['c'][0]=min(6,max(2,level));attr[0]=anchors[path]+'-'+attr[0]
        blocks.append(walk(block,path,anchors))
    if first:raise ValueError(f'Markdown缺少一级标题：{path}')
    blocks.append(walk(para('本节原文件：'+str(path.relative_to(ROOT))),path,anchors))

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--smoke',action='store_true',help='只构建少量内容，检查排版依赖');args=parser.parse_args()
    pandoc=require('pandoc');require('xelatex')
    try:import fitz
    except ImportError:raise SystemExit('缺少PyMuPDF：python3 -m pip install -r tools/requirements-pdf.txt')
    output=ROOT/'dist';work=ROOT/'build/pdf';output.mkdir(exist_ok=True);work.mkdir(parents=True,exist_ok=True)
    docs,code,extra=collect();all_files=docs+code+extra;anchors={p:identifier(p) for p in all_files}
    manifest=json.loads((ROOT/'data/source_manifest.json').read_text())
    for item in manifest:
        if digest(ROOT/item['source_path'])!=item['sha256']:raise SystemExit('原始PDF校验失败：'+item['source_path'])
    selected_docs=docs[:3] if args.smoke else docs
    selected_code=code[:2] if args.smoke else code
    selected_extra=[] if args.smoke else extra
    blocks=[para('阅读顺序：先走学习路线，再看基础知识与实验，最后对照完整C99/C++11代码。所有知识文档、任务卡与源代码均收录。代码为手机显示而折行，复制运行请使用仓库源文件；原始PDF完整保存在raw，附原件版会追加全部258页。'),para('统计以资料为依据：S1–S3共695次题目出现，含重复题；上机报告另有26项任务。它们不是历年考试概率。')];api=[]
    for path in selected_docs:add_document(path,pandoc,anchors,blocks,api)
    examples=json.loads((ROOT/'data/examples.json').read_text());titles={e['id']:e['title'] for e in examples}
    for path in selected_code:
        if path.suffix=='.c':
            blocks += [{'t':'RawBlock','c':['latex','\\clearpage']},{'t':'Header','c':[1,['pair-'+path.stem,[],[]],text_inline(path.stem+' '+titles[path.stem])]}]
        blocks += [{'t':'Header','c':[2,[anchors[path],[],[]],text_inline('C99版本' if path.suffix=='.c' else 'C++11版本')]},para(str(path.relative_to(ROOT))),{'t':'CodeBlock','c':[['',[],[]],wrap_code(path.read_text())]}]
    for path in selected_extra:
        blocks += [{'t':'RawBlock','c':['latex','\\clearpage']},{'t':'Header','c':[1,[anchors[path],[],[]],text_inline('工具：'+path.name)]},walk(para(str(path.relative_to(ROOT))),path,anchors),{'t':'CodeBlock','c':[['',[],[]],wrap_code(path.read_text())]}]
    document={'pandoc-api-version':api,'meta':{},'blocks':blocks};ast=work/'book.json';ast.write_text(json.dumps(document,ensure_ascii=False))
    name='排版测试.pdf' if args.smoke else MOBILE
    destination=output/name
    command=[pandoc,str(ast),'--from=json','--to=latex','--standalone','--pdf-engine=xelatex','--toc','--toc-depth=1','--no-highlight','--include-in-header='+str(ROOT/'tools/pdf/header.tex'),'-V','documentclass=article','-V','geometry:paperwidth=108mm','-V','geometry:paperheight=192mm','-V','geometry:left=9mm','-V','geometry:right=9mm','-V','geometry:top=15mm','-V','geometry:bottom=14mm','-V','fontsize=12pt','-V','mainfont=Noto Sans CJK SC','-V','sansfont=Noto Sans CJK SC','-V','monofont=Noto Sans Mono CJK SC','-V','colorlinks=true','-V','linkcolor=teal','-V','urlcolor=teal','-M','title=大一 C 语言全面指南','-M','subtitle=C99 / C++11 · 知识、题型、实验与完整代码','-M','author=依据六份上传资料整理','-M','lang=zh-CN','-o',str(destination)]
    env=os.environ.copy();env['TEXMFVAR']=str(work/'tex-cache');env['XDG_CACHE_HOME']=str(work/'cache')
    print(f'正在排版：{len(selected_docs)}份Markdown、{len(selected_code)}份教学源代码、{len(selected_extra)}份工具与配置源码。',flush=True)
    result=subprocess.run(command,env=env,capture_output=True,text=True)
    (work/'pandoc.log').write_text(result.stdout+'\n'+result.stderr)
    if result.returncode:raise SystemExit('PDF排版失败，详见build/pdf/pandoc.log\n'+result.stderr[-2500:])
    book=fitz.open(destination)
    if args.smoke:print(f'排版测试通过：{len(book)}页，{destination}');return
    full=fitz.open(destination);toc=book.get_toc();guide_pages=len(book)
    toc.append([1,'原始资料 · 六份原PDF（未修改）',guide_pages+1])
    raw_entries=[]
    for item in manifest:
        raw=fitz.open(ROOT/item['source_path']);start=len(full)+1
        full.insert_pdf(raw);toc.append([2,item['id']+' '+Path(item['source_path']).name,start])
        raw_entries.append({'source':item['id'],'start_page':start,'pages':len(raw),'sha256':item['sha256']})
        raw.close()
    full.set_toc(toc);full.set_metadata({'title':'大一C语言全面指南 C99/C++11（含全部原始资料）','author':'依据用户上传资料整理','subject':'完整指南、所有代码、六份原始PDF'})
    full_path=output/COMPLETE;full.save(full_path,garbage=4,deflate=True)
    inventory={'markdown_files':[str(p.relative_to(ROOT)) for p in docs],'teaching_code_files':[str(p.relative_to(ROOT)) for p in code],'tool_code_files':[str(p.relative_to(ROOT)) for p in extra],'inputs':[{'path':str(p.relative_to(ROOT)),'sha256':digest(p)} for p in all_files],'mobile_page_points':[book[0].rect.width,book[0].rect.height],'mobile_pages':guide_pages,'complete_pages':len(full),'raw_appendices':raw_entries,'mobile_pdf':name,'complete_pdf':COMPLETE}
    (output/'pdf_manifest.json').write_text(json.dumps(inventory,ensure_ascii=False,indent=2)+'\n')
    print(f'已生成：手机阅读版{guide_pages}页；附原件版{len(full)}页。输出目录：{output}')
    full.close();book.close()
if __name__=='__main__':main()
