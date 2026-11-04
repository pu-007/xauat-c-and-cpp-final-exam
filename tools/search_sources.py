#!/usr/bin/env python3
"""例：python3 tools/search_sources.py 素数 --source S6 --context 120"""
from pathlib import Path
import argparse,json,re
R=Path(__file__).resolve().parents[1]
p=argparse.ArgumentParser(description=__doc__);p.add_argument('keyword');p.add_argument('--source',choices=['S1','S2','S3','S4','S5','S6']);p.add_argument('--context',type=int,default=90);args=p.parse_args()
for source in json.loads((R/'data/source_manifest.json').read_text()):
    if args.source and source['id']!=args.source:continue
    for page,text in enumerate(json.loads((R/f'data/sources/{source["id"]}.json').read_text()),1):
        position=text.lower().find(args.keyword.lower())
        if position>=0:
            excerpt=re.sub(r'\s+',' ',text[max(0,position-args.context):position+len(args.keyword)+args.context])
            print(f'{source["id"]} PDF p{page}: {excerpt}')
