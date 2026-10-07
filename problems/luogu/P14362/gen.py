#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    max_edges = n * (n - 1) // 2
    m = random.randint(n - 1, min(max_edges, n + 8))
    k = random.randint(0, 3)

    edges = set()
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        edges.add((min(i, p), max(i, p)))

    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        edges.add((min(u, v), max(u, v)))

    print(n, len(edges), k)
    for u, v in sorted(edges):
        print(u, v, random.randint(0, 30))

    for _ in range(k):
        c = random.randint(0, 30)
        costs = [str(random.randint(0, 30)) for _ in range(n)]
        print(c, *costs)


if __name__ == "__main__":
    main()
