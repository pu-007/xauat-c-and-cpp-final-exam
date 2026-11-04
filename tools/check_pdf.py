#!/usr/bin/env python3
"""检查PDF收录完整性、链接、字体嵌入、页面边界以及原件附录。"""
from pathlib import Path
import hashlib,json,re
import fitz
from build_pdf import collect
R=Path(__file__).resolve().parents[1]
manifest=json.loads((R/'dist/pdf_manifest.json').read_text())
docs,code,extra=collect()
assert manifest['markdown_files']==[str(p.relative_to(R)) for p in docs]
assert manifest['teaching_code_files']==[str(p.relative_to(R)) for p in code]
assert manifest['tool_code_files']==[str(p.relative_to(R)) for p in extra]
for item in manifest['inputs']:
    assert hashlib.sha256((R/item['path']).read_bytes()).hexdigest()==item['sha256'],f'PDF is stale: {item["path"]}'
guide=fitz.open(R/'dist'/manifest['mobile_pdf']);full=fitz.open(R/'dist'/manifest['complete_pdf'])
assert len(guide)==manifest['mobile_pages'] and len(full)==manifest['complete_pages']==len(guide)+258
compact=re.sub(r'\s+','', ''.join(page.get_text() for page in guide)).translate(str.maketrans({'‑':'-','‐':'-'}))
for filename in manifest['teaching_code_files']+manifest['tool_code_files']:
    assert re.sub(r'\s+','',filename) in compact,f'Missing code title: {filename}'
font_ids=set();links=0;overflow=[]
for number,page in enumerate(guide,1):
    assert abs(page.rect.width-306.14)<1 and abs(page.rect.height-544.25)<1
    for font in page.get_fonts():font_ids.add(font[0])
    for word in page.get_text('words'):
        if word[0]<-1 or word[1]<-1 or word[2]>page.rect.width+1 or word[3]>page.rect.height+1:overflow.append((number,word[:5]))
    for link in page.get_links():
        if link['kind'] in {fitz.LINK_GOTO,fitz.LINK_NAMED}:
            assert 0<=link.get('page',-1)<len(guide),f'Unresolved link on page {number}'
            links+=1
assert not overflow,overflow[:10]
assert all(guide.extract_font(xref)[3] for xref in font_ids), 'Unembedded font'
# PDF正文在附原件版中仍保留命名链接。
for page in list(full)[:len(guide)]:
    for link in page.get_links():
        if link['kind'] in {fitz.LINK_GOTO,fitz.LINK_NAMED}:assert 0<=link.get('page',-1)<len(guide)
sources=json.loads((R/'data/source_manifest.json').read_text())
for raw in manifest['raw_appendices']:
    source=next(item for item in sources if item['id']==raw['source'])
    original=fitz.open(R/source['source_path']);assert len(original)==raw['pages']
    for index,page in enumerate(original):
        appended=full[raw['start_page']-1+index]
        assert page.get_text()==appended.get_text() and page.rect==appended.rect
    original.close()
assert len(full.get_toc())>=len(guide.get_toc())+7
print(f'PASS PDF: {len(docs)} Markdown, {len(code)} teaching files, {len(extra)} tool/config files, {links} internal links, {len(font_ids)} embedded fonts; {len(guide)}/{len(full)} pages; all 258 raw pages matched')
