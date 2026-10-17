#!/usr/bin/env python3
"""生成 P3371 的随机小数据：有向图，w >= 0，允许重边，用于对拍。"""
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 8)
    m = random.randint(0, 20)
    s = random.randint(1, n)
    maxw = random.choice([1, 3, 10, 100])

    print(n, m, s)
    for _ in range(m):
        u = random.randint(1, n)
        v = random.randint(1, n)
        w = random.randint(0, maxw)
        print(u, v, w)


if __name__ == "__main__":
    main()
