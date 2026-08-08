#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    max_edges = n * (n - 1) // 2
    m = random.randint(0, min(max_edges, n + 30))

    edges = set()
    while len(edges) < m:
        u = random.randint(0, n - 1)
        v = random.randint(0, n - 1)
        if u == v:
            continue
        edges.add((min(u, v), max(u, v)))

    k = random.randint(0, n)
    order = random.sample(range(n), k)

    print(n, len(edges))
    for u, v in sorted(edges):
        print(u, v)
    print(k)
    for x in order:
        print(x)


if __name__ == "__main__":
    main()
