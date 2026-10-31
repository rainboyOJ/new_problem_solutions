"""P17832 对拍生成器：先串起各条线路，再补站点，保证连通和每站线路数上限。"""
import argparse
import os
import sys
from random import seed
from cyaron import IO, randint


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--n', type=int, help='线路数，默认 1..8')
    parser.add_argument('--m', type=int, help='站数，需至少 n+1')
    parser.add_argument('--d', type=int, help='每站线路数上限，多线路时需至少 2')
    parser.add_argument('--q', type=int, help='询问数，默认 5..15')
    parser.add_argument('--max-weight', type=int, default=10**9)
    args = parser.parse_args()
    if 'DUPAI_SEED' in os.environ:
        seed(int(os.environ['DUPAI_SEED']))  # cyaron 也使用此随机源，便于重现
    case_id = int(os.environ.get('DUPAI_CASE_ID', '1'))
    n = args.n if args.n is not None else randint(1, 8)
    m = args.m if args.m is not None else randint(n + 1, n + 10)
    d = args.d if args.d is not None else (1 if n == 1 else randint(2, min(n, 4)))
    q = args.q if args.q is not None else randint(5, 15)
    if not (1 <= n <= 500 and n + 1 <= m <= 500000 and
            1 <= d <= 20 and (n == 1 or d >= 2) and
            1 <= q <= 100000 and 1 <= args.max_weight <= 10**9):
        parser.error('规模或数值范围不合法；本生成器要求 m>=n+1，多线路时 d>=2')

    # 第 i 条线先经过站 i、i+1，各条线串成一条链，每站至多两条线。
    lines = [set() for _ in range(n)]
    degree = [0] * (m + 1)
    for i in range(n):
        for v in [i + 1, i + 2]:
            lines[i].add(v)
            degree[v] += 1
    for v in range(n + 2, m + 1):
        lines[randint(0, n - 1)].add(v)
        degree[v] = 1
    total = sum(map(len, lines))
    if total > 500000:
        parser.error('线路与站点的关联总数超过 500000')

    # 只有真正新增一次“线路经过站点”的关系，才增加该站的线路数。
    for stations in lines:
        for _ in range(randint(0, 4)):
            v = randint(1, m)
            if v not in stations and degree[v] < d and total < 500000:
                stations.add(v)
                degree[v] += 1
                total += 1

    bound = 20 if case_id % 2 == 0 else args.max_weight
    bound = min(bound, args.max_weight)
    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(0, n, m, d, q)
    io.input_writeln([randint(1, bound) for _ in range(m)])
    uniform_walk = randint(1, bound)
    for stations in lines:
        row = [len(stations)]
        for v in sorted(stations, reverse=case_id % 2 == 0):
            walk = uniform_walk if case_id % 4 == 0 else randint(1, bound)
            row.extend([v, walk])
        io.input_writeln(row)
    for _ in range(q):
        x = randint(1, m)
        y = randint(1, m - 1)
        if y >= x:
            y += 1
        io.input_writeln(x, y)


if __name__ == '__main__':
    main()
