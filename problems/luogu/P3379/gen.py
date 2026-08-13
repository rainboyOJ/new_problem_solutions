#!/usr/bin/env python3
"""随机小树生成器：n <= 30，m 次随机查询，配合 brute.cpp 对拍。"""

import random


def main():
    random.seed()
    n = random.randint(1, 30)
    m = random.randint(1, 50)
    root = random.randint(1, n)

    edges = []
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        edges.append((parent, i))

    print(n, m, root)
    for u, v in edges:
        print(u, v)
    for _ in range(m):
        x = random.randint(1, n)
        y = random.randint(1, n)
        print(x, y)


if __name__ == "__main__":
    main()
