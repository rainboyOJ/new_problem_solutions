#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    max_edges = n * (n - 1) // 2
    m = random.randint(n - 1, min(max_edges, 15))

    edges = {}

    # 先造一棵树，保证连通。
    for i in range(2, n + 1):
        fa = random.randint(1, i - 1)
        key = (min(i, fa), max(i, fa))
        edges[key] = random.randint(1, 6)

    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        key = (min(u, v), max(u, v))
        if key in edges:
            continue
        edges[key] = random.randint(1, 6)

    print(n, len(edges))
    for (u, v), w in edges.items():
        print(u, v, w)


if __name__ == "__main__":
    main()
