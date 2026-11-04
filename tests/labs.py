#!/usr/bin/env python3
"""实验报告新增任务：独立预期、并列鞍点、增删改查模型、磁盘二进制验证。"""
import run
from run import check,BASE,R
from pathlib import Path
import random,subprocess,tempfile,ctypes,sys,json
rng=random.Random(20261104)
for data,out in [('0 2 -4','LINEAR 2.000000\n'),('0 0 0','ALL\n'),('0 0 2','NONE\n'),('1 -2 1','REAL 1.000000 1.000000\n'),('1 2 5','COMPLEX -1.000000 2.000000\n'),('-1 -2 -5','COMPLEX -1.000000 2.000000\n')]:check('37_quadratic',data,out)
for s,out in [('', 'INVALID'),('+','INVALID'),(' 2','INVALID'),('12x','INVALID'),('00012','12'),('+0','0'),('-0','0'),('2147483647','2147483647'),('-2147483648','-2147483648'),('2147483648','INVALID'),('-2147483649','INVALID'),('9'*100,'INVALID')]:check('40_my_atoi',s+'\n',out+'\n')
for _ in range(30):
    rows=rng.randint(1,5);cols=rng.randint(1,5);a=[[rng.randint(-3,3) for _ in range(cols)] for _ in range(rows)]
    points=[f'{r} {c} {a[r][c]}' for r in range(rows) for c in range(cols) if a[r][c]==max(a[r]) and a[r][c]==min(a[i][c] for i in range(rows))]
    check('39_saddle',f'{rows} {cols}\n'+'\n'.join(' '.join(map(str,row)) for row in a)+'\n','\n'.join(points or ['NONE'])+'\n')
for a in [list(range(10)),[5]*10,list(range(10,0,-1))]:check('12_sort','10\n'+' '.join(map(str,a)),' '.join(map(str,sorted(a)))+'\n'+' '.join(map(str,sorted(a)))+'\n'+' '.join(map(str,sorted(a)))+'\n')
check('19_students','2\n1 A 80 80 80\n2 B 80 80 80\n','80.00 80.00 80.00\n1 A 80.00\n1 2\n')
# 用Python有序字典作为业务模型；含重复编号、删除首尾/全部、修改不存在记录。
state={};commands=[];expected=[]
for _ in range(220):
    op=rng.randint(1,5);id=rng.randint(1,12);people=rng.randint(1,20);time=f'{rng.randrange(24):02d}:{rng.randrange(60):02d}'
    if op==1:
        commands.append(f'1 {id} N{id} {people} {time}')
        if id in state:expected.append('DUPLICATE')
        else:state[id]=(f'N{id}',people,time);expected.append('OK')
    elif op==2:
        commands.append(f'2 {id}');expected.append(f'{id} '+ ' '.join(map(str,state[id])) if id in state else 'NOT_FOUND')
    elif op==3:
        commands.append(f'3 {id} {people} {time}')
        if id in state:state[id]=(state[id][0],people,time);expected.append('OK')
        else:expected.append('NOT_FOUND')
    elif op==4:
        commands.append(f'4 {id}');expected.append('OK' if id in state else 'NOT_FOUND');state.pop(id,None)
    else:
        commands.append('5');expected.extend([f'{key} '+' '.join(map(str,value)) for key,value in state.items()] or ['EMPTY'])
commands.append('6');check('44_reservations','\n'.join(commands)+'\n','\n'.join(expected)+'\n')
check('44_reservations','1 1 A 2 12:00\n3 1 0 12:00\n3 1 3 24:00\n2 1\n1 2 B 2 23:60\nfoo\n5 extra\n4 1\n4 1\n5\n6\n','OK\nINVALID\nINVALID\n1 A 2 12:00\nINVALID\nINVALID\nINVALID\nOK\nNOT_FOUND\nEMPTY\n')
# 持久文件入口：验证终端、文本文件、原序二进制、排序二进制内容都正确。
e=next(x for x in json.loads((R/'data/examples.json').read_text()) if x['id']=='42_grade_files')
with tempfile.TemporaryDirectory(prefix='c-guide-test-') as folder:
    folder=Path(folder);source=folder/'input.txt';source.write_text(e['sample']);results=[]
    for lang in ['c','cpp']:
        text=folder/f'{lang}.txt';raw=folder/f'{lang}.raw';sorted_file=folder/f'{lang}.sorted'
        process=subprocess.run([str(BASE/lang/'42_grade_files'),str(source),str(text),str(raw),str(sorted_file)],text=True,capture_output=True,check=True,timeout=10)
        assert process.stdout==e['expected'] and text.read_text()==e['expected']
        width=ctypes.sizeof(ctypes.c_int);record=20+3*width
        for path,order in [(raw,list(range(10))),(sorted_file,list(reversed(range(10))))]:
            data=path.read_bytes();assert len(data)==10*record
            for i,value in enumerate(order):
                part=data[i*record:(i+1)*record];assert part[:20].split(b'\0')[0].decode()==f'S{value}'
                assert [int.from_bytes(part[20+j*width:20+(j+1)*width],sys.byteorder,signed=True) for j in range(3)]==[value]*3
        results.append((raw.read_bytes(),sorted_file.read_bytes()))
    assert results[0]==results[1]
print(f'PASS labs: {run.RUNS} process assertions + 2 persistent-file pipelines with byte-level validation; seed=20261104')
