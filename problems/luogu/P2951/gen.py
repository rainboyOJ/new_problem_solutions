#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 20)
    max_edges = n * (n - 1) // 2
    m = random.randint(n - 1, min(max_edges, 40))

    edges = set()

    # 先造一棵树，保证连通。
    for i in range(2, n + 1):
        fa = random.randint(1, i - 1)
        edges.add((min(i, fa), max(i, fa)))

    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        edges.add((min(u, v), max(u, v)))

    print(n, len(edges))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
