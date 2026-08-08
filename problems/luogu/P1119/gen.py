#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 12)
    max_edges = n * (n - 1) // 2
    m = random.randint(1, min(max_edges, 20))

    times = [random.randint(0, 10) for _ in range(n)]

    edges = {}
    for i in range(1, n):
        fa = random.randint(0, i - 1)
        key = (min(i, fa), max(i, fa))
        edges[key] = random.randint(1, 20)

    while len(edges) < m:
        u = random.randint(0, n - 1)
        v = random.randint(0, n - 1)
        if u == v:
            continue
        key = (min(u, v), max(u, v))
        if key in edges:
            continue
        edges[key] = random.randint(1, 20)

    q = random.randint(1, 20)

    print(n, len(edges))
    print(" ".join(map(str, times)))
    for (u, v), w in edges.items():
        print(u, v, w)
    print(q)
    for _ in range(q):
        x = random.randint(0, n - 1)
        y = random.randint(0, n - 1)
        t = random.randint(0, 10)
        print(x, y, t)


if __name__ == "__main__":
    main()
