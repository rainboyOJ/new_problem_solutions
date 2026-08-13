#!/usr/bin/env python3
"""随机生成一棵带权树和 m 条运输计划，配合 brute.cpp 对拍。

数据规模刻意保持很小：n <= 30, m <= 40，因为 brute.cpp 是 O(n*m) 的暴力。
"""
import random


def main():
    random.seed()
    n = random.randint(2, 30)
    m = random.randint(1, 40)

    print(n, m)
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        w = random.randint(0, 1000)
        print(parent, i, w)
    for _ in range(m):
        u = random.randint(1, n)
        v = random.randint(1, n)
        print(u, v)


if __name__ == "__main__":
    main()
