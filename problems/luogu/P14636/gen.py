"""P14636 小规模对拍：重复原价、倍数边界及大原价。"""
import os
import sys
from random import seed
from cyaron import IO, randint

if 'DUPAI_SEED' in os.environ: seed(int(os.environ['DUPAI_SEED']))
io=IO(input_file=sys.stdout,disable_output=True)
tests=randint(1,5)
io.input_writeln(0,tests)
for _ in range(tests):
    n=randint(1,9);m=randint(1,2*n-1);mode=randint(0,4)
    if mode==0:
        a=[randint(1,25) for _ in range(n)]
    elif mode==1:
        value=randint(1,10**9);a=[value]*n
    elif mode==2:
        value=randint(1,10**8);choices=[value,2*value,2*value+1]
        a=[choices[randint(0,2)] for _ in range(n)]
    elif mode==3:
        a=[randint(500000001,10**9) for _ in range(n)]
    else:
        a=[randint(1,5) for _ in range(n)]
    io.input_writeln(n,m);io.input_writeln(a)
