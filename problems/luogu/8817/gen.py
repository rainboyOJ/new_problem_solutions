#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(5, 10)
    possible = [(i, j) for i in range(1, n + 1) for j in range(i + 1, n + 1)]
    random.shuffle(possible)

    edges = set()
    for i in range(1, n):
        edges.add((i, i + 1))
    extra = random.randint(0, min(15, len(possible)))
    for e in possible[:extra]:
        edges.add(e)

    m = len(edges)
    k = random.randint(0, 4)
    print(n, m, k)
    print(*[random.randint(1, 100) for _ in range(n - 1)])
    for u, v in sorted(edges):
        print(u, v)


if __name__ == "__main__":
    main()
