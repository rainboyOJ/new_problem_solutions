#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 30)
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))

    random.shuffle(all_edges)
    p = random.randint(1, min(len(all_edges), 100))
    k = random.randint(1, p)

    print(n, p, k)
    for i in range(p):
        u, v = all_edges[i]
        w = random.randint(1, 1000)
        print(u, v, w)


if __name__ == "__main__":
    main()
