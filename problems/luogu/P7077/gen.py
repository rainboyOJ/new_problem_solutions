#!/usr/bin/env python3
"""P7077 随机数据生成器。

关键点：函数编号顺序和调用 DAG 的拓扑序无关。
生成时先随机一个“求值顺序”，再只允许函数调用排在它前面的函数，
这样既保证无环，又会让编号大的函数调用编号小的函数、编号小的函数
也能调用编号大的函数，从而真正考验拓扑排序。
"""
import argparse
import random

MOD = 998244353


def parse_args():
    parser = argparse.ArgumentParser(description="Generate random test data for P7077.")
    parser.add_argument("--max-n", type=int, default=6, help="数组长度上限")
    parser.add_argument("--max-m", type=int, default=8, help="函数个数上限")
    parser.add_argument("--max-q", type=int, default=6, help="总调用序列长度上限")
    parser.add_argument("--max-c", type=int, default=3, help="3 类函数最多调用的函数个数")
    return parser.parse_args()


def main():
    args = parse_args()
    random.seed()

    n = random.randint(1, args.max_n)
    a = [random.randint(0, 10) for _ in range(n)]
    m = random.randint(1, args.max_m)

    # eval_order 是一个随机排列，排在后面的函数只能调用排在它前面的函数。
    eval_order = list(range(1, m + 1))
    random.shuffle(eval_order)

    funcs = [None] * (m + 1)
    for i, fid in enumerate(eval_order):
        candidates = eval_order[:i]   # 只能调用更早求值的函数，保证无环
        if not candidates:
            # 第一个求值的函数没人可调用，只能是 1 类或 2 类。
            typ = random.randint(1, 2)
        else:
            typ = random.randint(1, 3)

        if typ == 1:
            funcs[fid] = (1, random.randint(1, n), random.randint(0, 10))
        elif typ == 2:
            funcs[fid] = (2, random.randint(0, 5))
        else:
            c = random.randint(1, min(args.max_c, len(candidates)))
            funcs[fid] = (3, random.sample(candidates, c))

    qnum = random.randint(1, args.max_q)
    queries = [random.randint(1, m) for _ in range(qnum)]

    print(n)
    print(*a)
    print(m)
    for i in range(1, m + 1):
        item = funcs[i]
        if item[0] == 1:
            _, p, v = item
            print(1, p, v % MOD)
        elif item[0] == 2:
            _, v = item
            print(2, v % MOD)
        else:
            _, seq = item
            print(3, len(seq), *seq)
    print(qnum)
    print(*queries)


if __name__ == "__main__":
    main()
