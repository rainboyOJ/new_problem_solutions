#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)

    edges = set()
    max_m = n * (n - 1) // 2
    m = random.randint(0, max_m)

    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        if u > v:
            u, v = v, u
        edges.add((u, v))

    print(n, len(edges))
    for u, v in sorted(edges):
        print(u, v)


if __name__ == "__main__":
    main()
