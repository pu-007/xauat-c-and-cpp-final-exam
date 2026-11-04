#!/usr/bin/env python3
"""重建资料统计。精确计数来自人工核对的分节题号；关键词覆盖仅作检索，绝不是考频。"""
from pathlib import Path
import json,re,csv,collections,unicodedata
R=Path(__file__).resolve().parents[1]
pages={s:json.loads((R/f'data/sources/{s}.json').read_text()) for s in ['S1','S2','S3','S4','S5','S6']}
# 分节人工核对，题量按一级题号，不按空格数或子问数。页码为PDF物理页。
chapters=[('程序基础',2,3,[15,0,6,0]),('顺序与输入输出',4,7,[7,7,5,5]),('分支',8,14,[8,6,6,7]),('循环',15,23,[6,10,7,23]),('数组',24,34,[7,8,9,25]),('函数',35,42,[13,11,4,14]),('指针',43,61,[36,27,4,10]),('结构体共用体',62,78,[16,8,10,10]),('文件',79,82,[6,0,4,8])]
registry=[]
for name,start,end,counts in chapters:
    for kind,count in zip(['选择','读程序','填空','编程'],counts):
        if count:registry.append(dict(source='S1',section=name,type=kind,count=count,start=start,end=end,method='逐节末题号核对；填空不拆子问'))
registry.append(dict(source='S1',section='附加题',type='综合编程',count=94,start=83,end=102,method='题号1–94；94跨p99–102'))
for name,start,end,counts in [('模拟一',103,109,[10,7,3,7,3]),('模拟二',109,115,[10,7,3,7,3]),('模拟三',115,121,[15,5,4,10,4])]:
    for kind,count in zip(['选择','读程序','程序填空','概念填空','编程'],counts):registry.append(dict(source='S1',section=name,type=kind,count=count,start=start,end=end,method='卷面一级题号；分值见papers.json'))
for name,kind,count,start,end in [('选择','选择',43,1,7),('读程序-控制','读程序',21,8,21),('读程序-数组','读程序',13,22,31),('读程序-函数','读程序',8,31,36),('读程序-指针','读程序',7,36,40),('读程序-结构体','读程序',4,40,41),('程序填空','程序填空',8,42,44),('程序改错','改错',8,45,49),('编程','编程',13,50,55)]:registry.append(dict(source='S2',section=name,type=kind,count=count,start=start,end=end,method='逐节题号核对；无标点的10/20/改错6也计入'))
for name,kind,count,start,end in [('选择','选择',15,1,2),('判断','判断',10,2,2),('简答','简答',4,2,3),('编程','编程',1,4,4)]:registry.append(dict(source='S3',section=name,type=kind,count=count,start=start,end=end,method='简答1含5个子问，按1题计'))
(R/'data/section_counts.json').write_text(json.dumps(registry,ensure_ascii=False,indent=2)+'\n')
with (R/'data/section_counts.csv').open('w',newline='') as f:
    w=csv.DictWriter(f,fieldnames=list(registry[0]));w.writeheader();w.writerows(registry)
# 建立全页检索表，保留上下文，不把自动命中当作人工分类题数。
topics={'基础与类型':r'标识符|关键字|数据类型|字节|sizeof|main', '运算与分支':r'表达式|运算符|switch|else|短路', '输入输出':r'scanf|printf|getchar|putchar|输入输出', '循环':r'循环|for\s*\(|while\s*\(', '数组矩阵':r'数组|矩阵|方阵|杨辉|转置', '字符串':r'字符串|strlen|strcpy|strcat|strcmp', '函数递归':r'函数|递归|形参|实参', '指针':r'指针|地址|\*p\b', '结构体共用体':r'结构体|共用体|struct|union|typedef', '文件':r'文件|fopen|fread|fwrite|fclose', '排序查找':r'排序|查找|冒泡|起泡|选择法', '数值数论':r'素数|阶乘|水仙花|最大公约数|斐波|分数序列|迭代', '链表':r'链表|结点|节点', '搜索回溯':r'皇后|迷宫|过河|同渡|回溯'}
hits=[]
for sid,ps in pages.items():
    # 排除S1目录与答案，避免答案重现导致页命中膨胀。
    for n,text in enumerate(ps,1):
        if sid=='S1' and (n==1 or n>=122):continue
        for topic,regex in topics.items():
            m=re.search(regex,text,re.I)
            if m:hits.append(dict(source=sid,page=n,topic=topic,excerpt=re.sub(r'\s+',' ',text[max(0,m.start()-25):m.end()+65])))
with (R/'data/page_keyword_hits.csv').open('w',newline='') as f:
    w=csv.DictWriter(f,fieldnames=['source','page','topic','excerpt']);w.writeheader();w.writerows(hits)
# 自动题号候选用于跳转；明确不从这份文件算题量。
candidates=[]
for sid in ['S1','S2','S3']:
    for n,text in enumerate(pages[sid],1):
        if sid=='S1' and (n==1 or n>=122):continue
        for m in re.finditer(r'(?m)^\s*(\d{1,3})[．、.](?!\d)\s*',text):
            candidates.append(dict(source=sid,page=n,number=m[1],excerpt=re.sub(r'\s+',' ',text[m.end():m.end()+180]),status='自动检索候选，可能受跨页/公式影响，不作题量统计'))
(R/'data/question_candidates.json').write_text(json.dumps(candidates,ensure_ascii=False,indent=2)+'\n')
# 精确题型分值来自卷面标题，原总分均为100。
papers=[{'paper':'S1模拟一','pages':'103–109','选择':20,'读程序':21,'程序填空':20,'概念填空':10,'编程':29},{'paper':'S1模拟二','pages':'109–115','选择':20,'读程序':21,'程序填空':20,'概念填空':10,'编程':29},{'paper':'S1模拟三','pages':'115–121','选择':15,'读程序':15,'程序填空':20,'概念填空':10,'编程':40},{'paper':'S3卷面模拟卷','pages':'1–4','选择':30,'判断':20,'简答含读程序':35,'编程':15}]
(R/'data/papers.json').write_text(json.dumps(papers,ensure_ascii=False,indent=2)+'\n')
lines=['# 资料题量、题型与复习优先级','', '统计的是这批上传资料，不能据此推断西建大历年真题概率。S3文件名写“真题”，但卷面标题写“模拟试题”，这里按模拟卷处理。没有考试年份序列、课程大纲或任课教师命题记录。','', '## 计数口径','', '- S1–S3按每节一级题号计题；同题跨资料重复保留，反映练习曝光量，不表示独立考次。','- 填空按题计，不按空计；S3简答1的5小问合为1题；S1模拟三最后一道编程3子问合为1题。','- S1 p122–133是答案，不重复计题；并非每道编程、附加题或模拟卷都附答案。','- S4是知识提纲，无统一题号；S5是教材例题与代码摘录，不和正式题库直接合计。','- 人工核对的分节题量保存在`data/section_counts.csv`；自动题号候选不参与统计。','', '## 核对后的分节题量','', '|资料/分节|选择|读程序|填空类|编程类|其他|总题数|PDF页|','|---|---:|---:|---:|---:|---:|---:|---|']
for sid,section in dict.fromkeys((r['source'],r['section']) for r in registry):
    rs=[r for r in registry if r['source']==sid and r['section']==section]; counts=collections.Counter()
    for r in rs:counts[r['type']]+=r['count']
    values=[counts['选择'],counts['读程序'],sum(counts[x] for x in ['填空','程序填空','概念填空']),counts['编程']+counts['综合编程'],sum(counts[x] for x in ['改错','判断','简答'])]
    lines.append(f'|{sid} {section}|'+ '|'.join(map(str,values))+f'|{sum(values)}|{rs[0]["start"]}–{rs[0]["end"]}|')
totals={sid:sum(r['count'] for r in registry if r['source']==sid) for sid in ['S1','S2','S3']}
lines+=['',f'合计：S1 **{totals["S1"]}** 题、S2 **{totals["S2"]}** 题、S3 **{totals["S3"]}** 题，共 **{sum(totals.values())}** 次题目出现；未去重。S1九单元共348题、附加94题、三套模拟卷98题。','', 'S1章节题量只能表示该章练习密度：指针77、数组49、循环46、结构体共用体44、函数42、分支27、顺序24、基础21、文件18。一个指针题也可能考循环，不能把这些数字解释为互斥知识点考频。','', '## 卷面题型与分值','', '|卷|选择|读程序|程序填空|概念填空|判断/简答|编程|','|---|---:|---:|---:|---:|---:|---:|']
for p in papers:lines.append(f'|{p["paper"]}（p{p["pages"]}）|{p.get("选择",0)}|{p.get("读程序",0)}|{p.get("程序填空",0)}|{p.get("概念填空",0)}|{p.get("判断",0)+p.get("简答含读程序",0)}|{p["编程"]}|')
lines+=['','S1三套期末模拟卷合计300分：选择55（18.3%），读程序57（19%），程序填空60（20%），概念填空30（10%），编程98（32.7%）。这是这三卷的加权分值分布，不是学校命题概率。S3单独保留，避免期中范围稀释期末指针、结构体与文件。','', '## 高频题族：有出处的复习排序','', '|题族|重复出现证据|优先级|仓库练习|','|---|---|---|---|','|表达式、分支、读程序|S1各单元/三模拟；S2选择10–16、控制读程序1–21；S3选择4/12、简答1–4；S4 p1–3|必会|01–05|','|数组极值、排序、矩阵|S1 p24–34及三模拟；S2数组13道读程序、填空8；S3选择5/14/15；S5 p2–6|必会|10–14、36|','|函数与指针|S1函数42题/指针77题；S2函数8道和指针7道读程序；S3选择6；S4 p3–5；S5 p3–8|必会|17–18、20、36|','|字符串、字符统计|S1 p30–32/42/61/120；S2选择41–43/填空1；S4 p4；S5 p3/7–8|必会|04、15–16|','|素数、阶乘、递推、水仙花|S1循环编程及模拟1/2/3；S2编程7/10/12；S5 p2/6/7|必会|05–09、23、36|','|结构体成绩|S1第八单元及模拟；S2选择30–34、结构体读程序1–4；S5 p6/9|必会|19、35|','|链表与文件|S1第八/九单元及模拟填空/编程；其他资料覆盖较少|次重点，但不能漏|20–21|','|回溯、迷宫、高精度|S1附加74/75/77/82|进阶|28–31|','|背包、前缀和、归并、KMP|部分由资料题型拓展，背包为新增|学有余力|25–27、31|','', '## 自动关键词页覆盖（检索辅助）','', '这是“出现某关键词的页数”，包含题干、代码、讲解，允许同页多标签；不能称为题数或考次。文件一词可能指源文件，main几乎到处出现，故此表只帮助跳转。规则与每个命中的页码、上下文均在`tools/analyze_sources.py`和`data/page_keyword_hits.csv`。','', '|检索主题|S1（排除目录/答案）|S2|S3|S4|S5|S6|','|---|---:|---:|---:|---:|---:|---:|']
for topic in topics:lines.append('|'+topic+'|'+'|'.join(str(sum(h['topic']==topic and h['source']==sid for h in hits)) for sid in pages)+'|')
lines+=['','## 人工校核记录','', '- S1 p22编程4/6的题号夹在公式排版中，仍计入；p23的22题抽取为“522”，原序列是22。','- S1附加题到94，不是p98的92；p99–102继续。','- S2控制读程序10/20没有句点，改错6也没有句点；均按完整题号序列计入。','- S5双栏直接按行抽取会串代码；保留`S5-columns.txt`作为阅读辅助，具体勘误另核对页面图像。','- S1 p128答案明确指出指针选择18/21重复，3/34重复；未将它们合并为独立题型。','- 当前没有逐道语义去重的全库统计；不得把695次题目出现称为695道独立题。','']
lines+=['', '## 新增上机报告S6：单独计实验任务', '', 'S6共52页、6次实验。前5次各5项（4项必做+1项选作），第6次1项综合项目，共26项，其中21项必做、5项选作。实验4第2项包含数组最大与my_atoi两个子任务，仍按一级编号计1项。实验任务与题库题目粒度不同，不加入695的合计。', '', '|实验|PDF页|任务数|必做/选作|主要知识|', '|---|---|---:|---|---|', '|1 选择与循环|1–7|5|4/1|闰年、二次方程、均分、水仙花、文件|', '|2 循环与数组|8–16|5|4/1|牛顿、排序、鞍点、字符串比较、文件|', '|3 函数与存储类型|17–26|5|4/1|素数、元音、static、全局数组、模块|', '|4 指针|27–36|5|4/1|swap、数组参数、atoi、拼接、动态内存、二进制|', '|5 结构体与链表|37–45|5|4/1|结构体数组/指针、链表、文件|', '|6 综合应用|46–52|1|1/0|订餐增删改查系统|', '', 'S6进一步强化数组、函数、指针、结构体与文件的重要性；实验出现次数不等于卷面出题概率。详细映射见15_labs.md。']
# S2/S3逐题主知识点标注：一题只指定一个主标签，交叉知识点不重复加权。
curated=[]
def tag(source,section,numbers,topic):
    record=next(r for r in registry if r['source']==source and r['section']==section)
    for number in numbers:
        curated.append(dict(source=source,section=section,number=number,primary_topic=topic,pdf_pages=f"{record['start']}–{record['end']}",method='按完整题意人工指定一个主知识点；页码是所在分节范围'))
for nums,topic in [(range(1,10),'基础与类型'),(range(10,17),'表达式'),(range(17,25),'数组'),(range(25,30),'函数与存储'),(range(30,35),'结构体'),(range(35,41),'指针'),(range(41,44),'字符串')]:tag('S2','选择',nums,topic)
for section,count,topic in [('读程序-控制',21,'控制结构'),('读程序-数组',13,'数组'),('读程序-函数',8,'函数与存储'),('读程序-指针',7,'指针'),('读程序-结构体',4,'结构体')]:tag('S2',section,range(1,count+1),topic)
for nums,topic in [([1,5],'字符串'),([2,3,4],'控制结构'),([6,7,8],'数组')]:tag('S2','程序填空',nums,topic)
for nums,topic in [([1,6,7],'控制结构'),([2,4],'数组'),([3,8],'函数与存储'),([5],'输入输出/顺序计算')]:tag('S2','程序改错',nums,topic)
for nums,topic in [([1,2],'输入输出/顺序计算'),([3,4,5,6,7,8,9,10],'控制结构'),([11,12],'函数与存储'),([13],'数组')]:tag('S2','编程',nums,topic)
for nums,topic in [([1,2,8,9,10,13],'基础与类型'),([3],'输入输出/顺序计算'),([4,12],'表达式'),([5,14,15],'数组'),([6],'函数与存储'),([7,11],'控制结构')]:tag('S3','选择',nums,topic)
for nums,topic in [([1,7,8,9],'基础与类型'),([2,5,6,10],'控制结构'),([3],'字符串'),([4],'数组')]:tag('S3','判断',nums,topic)
tag('S3','简答',[1],'表达式');tag('S3','简答',[2,3,4],'控制结构');tag('S3','编程',[1],'控制结构')
assert len(curated)==155 and len({(x['source'],x['section'],x['number']) for x in curated})==155
with (R/'data/curated_topic_map.csv').open('w',newline='') as f:
    writer=csv.DictWriter(f,fieldnames=list(curated[0]));writer.writeheader();writer.writerows(curated)
lines+=['', '## S2/S3逐题主知识点频次（人工标签）', '', '下表覆盖S2全部125题、S3全部30题，每题只指定一个主标签。函数式素数题归函数，数值循环题归控制结构；交叉知识点未额外加权。S1用前述章节题量，尚未逐题多标签编码。逐题编号、分节页码和标签见data/curated_topic_map.csv。', '', '|主知识点|S2题数|S2占比|S3题数|S3占比|', '|---|---:|---:|---:|---:|']
for topic in ['基础与类型','表达式','输入输出/顺序计算','控制结构','数组','字符串','函数与存储','指针','结构体']:
    a=sum(x['source']=='S2' and x['primary_topic']==topic for x in curated);b=sum(x['source']=='S3' and x['primary_topic']==topic for x in curated)
    lines.append(f'|{topic}|{a}|{a/125:.1%}|{b}|{b/30:.1%}|')
lines+=['', 'S2中控制结构35题、数组27题、函数与存储17题、指针13题，支持“先循环数组，再函数指针”的练习顺序。这个比例描述本练习册的题目分布，不是下一场考试的预测概率。']

(R/'docs/02_frequency.md').write_text('\n'.join(lines))
print('Source counts:',totals,'total',sum(totals.values()),'; retrieval candidates:',len(candidates))
