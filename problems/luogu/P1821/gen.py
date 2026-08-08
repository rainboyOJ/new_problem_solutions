#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 12)
    x = random.randint(1, n)

    edges = {}

    # 先保证所有点都能到 x。
    for i in range(1, n + 1):
        if i == x:
            continue
        w = random.randint(1, 20)
        edges[(i, x)] = min(edges.get((i, x), 10**9), w)

    # 再保证 x 能到所有点。
    for i in range(1, n + 1):
        if i == x:
            continue
        w = random.randint(1, 20)
        edges[(x, i)] = min(edges.get((x, i), 10**9), w)

    target_m = random.randint(len(edges), min(n * (n - 1), len(edges) + 20))
    while len(edges) < target_m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        w = random.randint(1, 20)
        key = (u, v)
        if key in edges:
            continue
        edges[key] = w

    print(n, len(edges), x)
    for (u, v), w in edges.items():
        print(u, v, w)


if __name__ == "__main__":
    main()
