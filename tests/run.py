#!/usr/bin/env python3
"""使用独立Python参考计算和边界数据，分别核对C/C++，并非仅比较两份实现。"""
from pathlib import Path
import json,subprocess,random,math,collections,sys,os
R=Path(__file__).resolve().parents[1]
BASE=Path(os.environ.get('COURSE_BIN',str(R/'build')))
RUNS=0

def check(slug,stdin,expected=None,code=0):
    global RUNS
    for lang in ('c','cpp'):
        result=subprocess.run([str(BASE/lang/slug)],input=stdin,text=True,capture_output=True,timeout=15)
        assert result.returncode==code,(lang,slug,stdin,result.returncode,result.stderr)
        if expected is not None: assert result.stdout==expected,(lang,slug,stdin,repr(result.stdout),repr(expected))
        RUNS+=1

def line(a):return ' '.join(map(str,a))+'\n'
def prime(n):return n>=2 and all(n%d for d in range(2,math.isqrt(n)+1))
def main():
    rng=random.Random(20261103)
    for e in json.loads((R/'data/examples.json').read_text()):check(e['id'],e['sample'],e['expected'])
    for n in range(101): check('03_grade',f'{n}\n',('A' if n>=90 else 'B' if n>=80 else 'C' if n>=70 else 'D' if n>=60 else 'E')+'\n')
    for n in [0,1,2,10,20]:check('05_factorial_sum',str(n),f'{math.factorial(n)} {sum(math.factorial(i) for i in range(1,n+1))}\n')
    for n in [-9,0,1,2,3,4,25,49,97,99991,1000000000]:check('08_prime',str(n),f'{int(prime(n))}\n')
    for n in [0,1,20,100,1000]:check('30_big_integer',str(n),str(math.factorial(n))+'\n')
    for n,count in [(1,1),(2,0),(3,0),(4,2),(5,10),(6,4),(7,40),(9,352),(10,724)]:check('28_queens',str(n),str(count)+'\n')
    for n in [0,1,2,30,100]:check('23_sieve',str(n),line([x for x in range(2,n+1) if prime(x)]))
    for s in ['', ' ', 'a  b\tC','AEIOUxyz']:
        vowels=''.join(c for c in s if c in 'aeiouAEIOU'); check('16_words_vowels',s+'\n',f'{len(s.split())}\n{vowels}\n'+''.join(sorted(s))+'\n')
    for a,b in [('', ''),('x',''),('a'*100,'b'*100),('level','level'),('abc','ab')]:
        check('15_strings',a+'\n'+b+'\n',f'{a+b}\n{len(a+b)} {(a>b)-(a<b)} {int(a==a[::-1])}\n')
    for _ in range(35):
        n=rng.randrange(0,30); a=[rng.randrange(-30,31) for _ in range(n)]; data=f'{n}\n'+line(a)
        check('12_sort',data,line(sorted(a))*3); check('25_merge_sort',data,line(sorted(a)))
        target=rng.randrange(-5,6); check('20_linked_list',f'{n} {target}\n'+line(a),line([x for x in a[::-1] if x!=target]))
        check('21_files',data,str(sum(a))+'\n')
        b=sorted(a); target=rng.randrange(-30,31)
        check('13_binary_search',f'{n} {target}\n'+line(b),str(b.index(target) if target in b else -1)+'\n')
        if n:
            k=rng.randrange(0,500); shifted=a[-(k%n):]+a[:-(k%n)] if k%n else a[:]
            first=shifted[:]; lo=shifted.index(min(shifted)); shifted[0],shifted[lo]=shifted[lo],shifted[0]
            hi=shifted.index(max(shifted)); shifted[-1],shifted[hi]=shifted[hi],shifted[-1]
            check('11_reverse_rotate',f'{n} {k}\n'+line(a),line(first)+line(shifted))
            k=rng.randint(1,n); sums=[sum(a[i:i+k]) for i in range(n-k+1)]; best=max(sums)
            check('26_prefix_window',f'{n} {k}\n'+line(a),f'{best} {sums.index(best)}\n')
        a0,b0=rng.randrange(10**9+1),rng.randrange(10**9+1);g=math.gcd(a0,b0)
        check('07_gcd',f'{a0} {b0}',f'{g} {math.lcm(a0,b0)}\n')
        check('24_recursion',f'{a0} {b0}',str(pow(a0,b0,1000000007))+'\n')
        text=''.join(rng.choices('abc ',k=rng.randrange(30))); pat=''.join(rng.choices('abc ',k=rng.randrange(6)))
        check('31_kmp',text+'\n'+pat+'\n',str(text.find(pat))+'\n')
    for _ in range(20):
        n=rng.randrange(9); cap=rng.randrange(15); items=[(rng.randrange(1,9),rng.randrange(20)) for _ in range(n)]
        best=max(sum(v for i,(w,v) in enumerate(items) if mask>>i&1) for mask in range(1<<n) if sum(w for i,(w,v) in enumerate(items) if mask>>i&1)<=cap)
        check('27_knapsack',f'{n} {cap}\n'+''.join(f'{w} {v}\n' for w,v in items),str(best)+'\n')
    for n in range(1,15):
        for k in [1,2,3,10]:
            alive=list(range(n));i=0
            while len(alive)>1:i=(i+k-1)%len(alive);alive.pop(i)
            check('22_josephus',f'{n} {k}',f'{alive[0]}\n')
    for n in [1,3,5,7,15]:
        for lang in ('c','cpp'):
            result=subprocess.run([str(BASE/lang/'34_magic_square')],input=str(n),text=True,capture_output=True,check=True)
            a=[list(map(int,row.split())) for row in result.stdout.splitlines()]; target=n*(n*n+1)//2
            assert len(a)==n and all(len(row)==n for row in a)
            assert sorted(sum(a,[]))==list(range(1,n*n+1))
            assert all(sum(row)==target for row in a) and all(sum(a[r][c] for r in range(n))==target for c in range(n))
            assert sum(a[i][i] for i in range(n))==target and sum(a[i][n-i-1] for i in range(n))==target
    for grid in [[[0]],[[1]],[[0,1],[1,0]],[[0,0],[1,0]]]:
        rows=len(grid);cols=len(grid[0]);dist={(0,0):0} if not grid[0][0] else {};q=collections.deque(dist)
        while q:
            r,c=q.popleft()
            for nr,nc in [(r+1,c),(r-1,c),(r,c+1),(r,c-1)]:
                if 0<=nr<rows and 0<=nc<cols and not grid[nr][nc] and (nr,nc) not in dist:dist[nr,nc]=dist[r,c]+1;q.append((nr,nc))
        check('29_bfs_maze',f'{rows} {cols}\n'+''.join(line(row) for row in grid),str(dist.get((rows-1,cols-1),-1))+'\n')
    for slug,data in [('03_grade','-1'),('03_grade','101'),('05_factorial_sum','21'),('10_array_stats','0'),('13_binary_search','2 1\n2 1'),('33_calendar','1900 2 29'),('34_magic_square','4'),('29_bfs_maze','21 1'),('15_strings','a'*101+'\nb\n'),('31_kmp','a'*1001+'\nb\n'),('02_io','x'),('19_students','1\n1 A 101 20 30')]:check(slug,data,code=1)
    check('07_gcd','0 0','0 0\n');check('33_calendar','1900 3 1','0 60\n')
    print(f'PASS: {RUNS} process assertions + 10 magic-square property checks; C99/C++11; seed=20261103')
if __name__=='__main__':main()
