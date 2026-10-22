#!/usr/bin/env python3
# 随机生成小数据：n 个区、m 条大道，保证 s 能到达 t（先造一棵生成树再补边）。
# 覆盖三种情形：无重边、有重边（题面允许两区之间多条大道）、s == t 的退化情形。
import random


def main():
    random.seed()

    n = random.randint(2, 7)
    s = random.randint(1, n)
    t = random.randint(1, n)
    # 一定比例生成 s == t 的退化数据，用来检查 0 的边界处理
    if random.random() < 0.15:
        t = s

    edges = []

    # 先造一棵树保证连通
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        edges.append((u, v, random.randint(1, 15)))

    # 再补一些边；这里故意允许同一对点出现多次，对应题面的「可能存在多条大道」
    extra = random.randint(0, n + 2)
    for _ in range(extra):
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        edges.append((u, v, random.randint(1, 15)))

    print(n, len(edges), s, t)
    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
