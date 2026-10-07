#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 10)
    max_edges = n * (n - 1) // 2
    m = random.randint(n - 1, min(max_edges, 20))

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

    weighted_edges = []
    for u, v in edges:
        weighted_edges.append((u, v, random.randint(1, 20)))

    print(n, len(weighted_edges))
    for u, v, w in weighted_edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
