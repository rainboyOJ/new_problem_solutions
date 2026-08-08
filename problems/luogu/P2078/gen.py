#!/usr/bin/env python3
import random


def rand_edges(limit, cnt):
    edges = []
    for _ in range(cnt):
        x = random.randint(1, limit)
        y = random.randint(1, limit)
        edges.append((x, y))
    return edges


def main():
    random.seed()

    n = random.randint(1, 8)
    m = random.randint(1, 8)
    p = random.randint(0, 10)
    q = random.randint(0, 10)

    ea = rand_edges(n, p)
    eb = rand_edges(m, q)

    print(n, m, p, q)
    for x, y in ea:
        print(x, y)
    for x, y in eb:
        print(-x, -y)


if __name__ == "__main__":
    main()
