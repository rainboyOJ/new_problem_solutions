#!/usr/bin/env python3
"""为 P2860 生成小规模连通无向图（允许重边）。"""
import random
import sys


def main():
    random.seed()

    n = random.randint(2, 6)
    # 先造一棵随机树，保证连通；m 的下界是 n-1
    edges = []
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        edges.append((u, v))

    extra = random.randint(0, n)  # 再加一些边，可能包含重边
    for _ in range(extra):
        u = random.randint(1, n)
        v = random.randint(1, n)
        while v == u:
            v = random.randint(1, n)
        edges.append((u, v))

    if random.random() < 0.5:
        random.shuffle(edges)

    print(n, len(edges))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
