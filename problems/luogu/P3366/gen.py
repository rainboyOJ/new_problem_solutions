#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 7)
    max_edges = n * (n - 1) // 2
    m = random.randint(0, min(max_edges, 15))

    edges = set()
    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        edges.add((min(u, v), max(u, v)))

    print(n, len(edges))
    for u, v in sorted(edges):
        print(u, v, random.randint(1, 50))


if __name__ == "__main__":
    main()
