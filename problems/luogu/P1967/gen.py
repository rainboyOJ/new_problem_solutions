#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))

    random.shuffle(all_edges)
    max_m = min(len(all_edges), 80)
    m = random.randint(0, max_m)
    q = random.randint(1, 50)

    print(n, m)
    for i in range(m):
        u, v = all_edges[i]
        w = random.randint(0, 1000)
        print(u, v, w)

    print(q)
    for _ in range(q):
        x = random.randint(1, n)
        y = random.randint(1, n)
        while n > 1 and y == x:
            y = random.randint(1, n)
        print(x, y)


if __name__ == "__main__":
    main()
