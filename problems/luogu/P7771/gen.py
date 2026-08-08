#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 7)
    edges = []

    # 先造一棵无向生成树，保证弱连通。
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        if random.randint(0, 1):
            edges.append((u, v))
        else:
            edges.append((v, u))

    extra = random.randint(0, 7)
    for _ in range(extra):
        u = random.randint(1, n)
        v = random.randint(1, n)
        edges.append((u, v))

    print(n, len(edges))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
