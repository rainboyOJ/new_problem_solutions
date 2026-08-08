#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 12)
    m = random.randint(1, min(n * (n - 1), 30))
    t = random.randint(1, 20)

    edges = set()
    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        h = random.randint(1, 30)
        edges.add((u, v, h))

    print(n, len(edges), t)
    for u, v, h in edges:
        print(u, v, h)

    for _ in range(t):
        a = random.randint(1, n)
        b = random.randint(1, n)
        print(a, b)


if __name__ == "__main__":
    main()
