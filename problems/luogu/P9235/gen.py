#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 12)
    max_m = n * (n - 1) // 2
    m = random.randint(n - 1, min(max_m, n + 8))
    q = random.randint(1, 20)

    edges = []
    used = set()

    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        u, v = min(i, p), max(i, p)
        w = random.randint(1, 20)
        edges.append((u, v, w))
        used.add((u, v))

    cand = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            if (i, j) not in used:
                cand.append((i, j))
    random.shuffle(cand)

    add_cnt = m - (n - 1)
    for i in range(add_cnt):
        u, v = cand[i]
        w = random.randint(1, 20)
        edges.append((u, v, w))

    random.shuffle(edges)

    print(n, len(edges), q)
    for u, v, w in edges:
        print(u, v, w)

    for _ in range(q):
        x = random.randint(1, n)
        y = random.randint(1, n)
        while y == x:
            y = random.randint(1, n)
        print(x, y)


if __name__ == "__main__":
    main()
