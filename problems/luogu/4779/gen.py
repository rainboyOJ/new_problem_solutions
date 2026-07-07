#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 40)
    s = 1
    edges = []
    for i in range(2, n + 1):
        u = random.randint(1, i - 1)
        w = random.randint(0, 30)
        edges.append((u, i, w))
    extra = random.randint(0, n * 3)
    for _ in range(extra):
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        w = random.randint(0, 30)
        edges.append((u, v, w))
    print(n, len(edges), s)
    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
