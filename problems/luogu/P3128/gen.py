#!/usr/bin/env python3
"""随机生成小规模树 + 随机路径，用于 main.cpp 与 brute.cpp 对拍。

- n <= 30，k 条随机路径（端点允许相同，覆盖 u == v 的边界）；
- 树按“每个点随机选一个更小编号作为父亲”生成，保证连通且无环。
"""
import random


def main():
    random.seed()
    n = random.randint(2, 30)
    k = random.randint(1, 60)

    print(n, k)
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(parent, i)
    for _ in range(k):
        u = random.randint(1, n)
        v = random.randint(1, n)
        print(u, v)


if __name__ == "__main__":
    main()
