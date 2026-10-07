#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 12)
    max_edges = n * (n - 1) // 2
    m = random.randint(n - 1, min(max_edges, 20))
    b = random.randint(1, 20)

    edges = {}

    # 先造一棵树，保证连通。
    for i in range(2, n + 1):
        fa = random.randint(1, i - 1)
        w = random.randint(1, 20)
        key = (min(i, fa), max(i, fa))
        edges[key] = w

    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        key = (min(u, v), max(u, v))
        if key in edges:
            continue
        edges[key] = random.randint(1, 20)

    print(n, len(edges), b)
    for (u, v), w in edges.items():
        print(u, v, w)
    for _ in range(b):
        p = random.randint(1, n)
        q = random.randint(1, n)
        print(p, q)


if __name__ == "__main__":
    main()
