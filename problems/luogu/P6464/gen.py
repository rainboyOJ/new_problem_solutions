#!/usr/bin/env python3
# 随机生成小数据：n 个点、m 条边，保证连通且无重边无自环。
import random


def main():
    random.seed()
    n = random.randint(2, 6)
    edges = set()

    # 先连成一棵树，保证连通
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        edges.add((u, v))

    # 再随机补一些边，注意不加重边
    extra = random.randint(0, n)
    for _ in range(extra):
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        if u > v:
            u, v = v, u
        edges.add((u, v))

    edges = sorted(edges)
    print(n, len(edges))
    for u, v in edges:
        print(u, v, random.randint(1, 100))


if __name__ == "__main__":
    main()
