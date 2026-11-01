"""P17833 小规模对拍数据，覆盖不连通、等差、密集及大坐标。"""
import argparse
import os
import sys
from random import seed
from cyaron import IO, randint


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--max-n', type=int, default=30)
    args = parser.parse_args()
    if not 1 <= args.max_n <= 300:
        parser.error('对拍使用 BFS 暴力，max-n 需在 1..300 内')
    if 'DUPAI_SEED' in os.environ:
        seed(int(os.environ['DUPAI_SEED']))
    io = IO(input_file=sys.stdout, disable_output=True)
    tests = randint(2, 5)
    io.input_writeln(0, tests)
    for _ in range(tests):
        n = randint(1, args.max_n)
        mode = randint(0, 4)
        d = randint(1, 20)
        coords = [0]
        step = randint(1, 8)
        for _ in range(n - 1):
            coords.append(coords[-1] + (step if mode == 1 else randint(1, 8)))
        if mode == 2:
            d = 1
        if mode == 3:
            d = 2 * 10**18
        shift = randint(-100, 100)
        if mode == 4:
            shift = -10**18 if randint(0, 1) else 10**18 - coords[-1]
        io.input_writeln(n, d)
        io.input_writeln([x + shift for x in coords])


if __name__ == '__main__':
    main()
