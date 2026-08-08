#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    edges = set()

    # 先造一棵树，保证基础连通。
    for v in range(2, n + 1):
        u = random.randint(1, v - 1)
        edges.add((u, v))

    extra = random.randint(0, 6)
    for _ in range(extra):
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v:
            continue
        if u > v:
            u, v = v, u
        edges.add((u, v))

    order = list(range(1, n + 1))
    random.shuffle(order)

    print(n, len(edges))
    for u, v in sorted(edges):
        print(u, v)
    for x in order:
        print(x)


if __name__ == "__main__":
    main()
