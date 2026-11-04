#!/usr/bin/env python3
"""可选：从已保存原PDF重建逐页文本。依赖PyMuPDF，正常练习/构建不需要此依赖。"""
from pathlib import Path
import json,hashlib
import fitz
R=Path(__file__).resolve().parents[1]
manifest=json.loads((R/'data/source_manifest.json').read_text())
for source in manifest:
    path=R/source['source_path']
    assert hashlib.sha256(path.read_bytes()).hexdigest()==source['sha256'],f'PDF changed: {path}'
    document=fitz.open(path);pages=[page.get_text(sort=True) for page in document];sid=source['id']
    assert len(pages)==source['pages']
    (R/f'data/sources/{sid}.json').write_text(json.dumps(pages,ensure_ascii=False,indent=2))
    (R/f'data/sources/{sid}.txt').write_text('\n'.join(f'\n===== PDF第{i}页 =====\n{t}' for i,t in enumerate(pages,1)))
    if sid=='S5':
        columns=[]
        for page in document:
            rect=page.rect
            columns.append('\n'.join(page.get_text(clip=fitz.Rect(left,25,right,rect.height-25),sort=True) for left,right in [(0,rect.width/2),(rect.width/2,rect.width)]))
        (R/'data/sources/S5-columns.json').write_text(json.dumps(columns,ensure_ascii=False,indent=2))
        (R/'data/sources/S5-columns.txt').write_text('\n'.join(f'\n===== PDF第{i}页 =====\n{t}' for i,t in enumerate(columns,1)))
    print(f'{sid}: {len(pages)} pages extracted; SHA-256 verified')
