#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    k = random.randint(1, min(8, n))
    m = random.randint(n - 1, min(n * (n - 1) // 2, 14))
    s, t = random.sample(range(1, n + 1), 2)

    culture = [0] + [random.randint(1, k) for _ in range(n)]

    hate = [[0] * (k + 1) for _ in range(k + 1)]
    for i in range(1, k + 1):
        for j in range(1, k + 1):
            if i == j:
                hate[i][j] = 0
            else:
                hate[i][j] = random.randint(0, 1)

    edges = set()
    for i in range(2, n + 1):
        fa = random.randint(1, i - 1)
        edges.add((min(i, fa), max(i, fa), random.randint(1, 20)))

    while len(edges) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        a, b = min(u, v), max(u, v)
        w = random.randint(1, 20)
        edges.add((a, b, w))

    print(n, k, len(edges), s, t)
    print(" ".join(str(culture[i]) for i in range(1, n + 1)))
    for i in range(1, k + 1):
        print(" ".join(str(hate[i][j]) for j in range(1, k + 1)))
    for u, v, d in edges:
        print(u, v, d)


if __name__ == "__main__":
    main()
