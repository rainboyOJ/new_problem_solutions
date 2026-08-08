#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 25)
    max_edges = n * (n - 1) // 2
    m = random.randint(n - 1, min(max_edges, n + 30))
    blood = random.randint(0, 80)

    print(n, m, blood)
    print("\n".join(str(random.randint(1, 30)) for _ in range(n)))

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

    for u, v in sorted(edges):
        print(u, v, random.randint(0, 30))


if __name__ == "__main__":
    main()
