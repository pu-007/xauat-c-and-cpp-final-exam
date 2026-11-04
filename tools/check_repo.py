#!/usr/bin/env python3
"""验证文档本地链接、案例成对覆盖、资料页数/哈希、统计总数。"""
from pathlib import Path
from urllib.parse import unquote
import json,re,hashlib
R=Path(__file__).resolve().parents[1]
errors=[];links=0
for path in R.rglob('*.md'):
    if '.git' in path.parts:continue
    text=path.read_text()
    text=re.sub(r'```.*?```','',text,flags=re.S)
    text=re.sub(r'`[^`]*`','',text)
    for target in re.findall(r'(?<!!)\[[^\]]+\]\(([^)]+)\)',text):
        if target.startswith(('http:','https:','#','mailto:')):continue
        target=unquote(target.split('#')[0]).strip('<>')
        if not (path.parent/target).exists():errors.append(f'{path.relative_to(R)}: {target}')
        links+=1
examples=json.loads((R/'data/examples.json').read_text());assert len(examples)==45
for e in examples:
    for lang in ['c','cpp']:assert (R/f'src/{lang}/{e["id"]}.{lang}').is_file()
    for suffix,key in [('in','sample'),('out','expected')]:assert (R/f'tests/cases/{e["id"]}.{suffix}').read_text()==e[key]
    assert (R/f'practice/tasks/{e["id"]}.md').is_file()
manifest=json.loads((R/'data/source_manifest.json').read_text());assert len(manifest)==6 and sum(s['pages'] for s in manifest)==258
for s in manifest:
    assert hashlib.sha256((R/s['source_path']).read_bytes()).hexdigest()==s['sha256']
    assert len(json.loads((R/f'data/sources/{s["id"]}.json').read_text()))==s['pages']
counts=json.loads((R/'data/section_counts.json').read_text());assert sum(r['count'] for r in counts)==695
for e in errors:print('BROKEN:',e)
assert not errors
print(f'PASS repository: {links} local links, 45 paired examples, 6 PDFs / 258 pages, 695 numbered occurrences')
