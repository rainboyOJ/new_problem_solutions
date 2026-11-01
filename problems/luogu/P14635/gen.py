"""P14635 对拍：小预算覆盖完整背包，large 模式与原二分解比较。"""
import argparse
import os
import sys
from random import seed
from cyaron import IO, randint


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--large', action='store_true')
    args=parser.parse_args()
    if 'DUPAI_SEED' in os.environ: seed(int(os.environ['DUPAI_SEED']))
    io=IO(input_file=sys.stdout,disable_output=True)
    mode=randint(0,4)
    n=randint(1,100) if args.large else randint(1,24)
    m=randint(1,10**18) if args.large else randint(1,204)
    bound=10**9 if args.large or mode==4 else 30
    io.input_writeln(n,m)
    for _ in range(n):
        x,y=randint(1,bound),randint(1,bound)
        if mode==1: y=x
        if mode==2: x,y=max(x,y),min(x,y)
        if mode==3: x=1
        io.input_writeln(x,y)


if __name__=='__main__':main()
