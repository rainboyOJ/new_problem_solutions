#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(2, 8)
    edges = []
    indeg = [0] * (n + 1)

    for u in range(1, n + 1):
        for v in range(u + 1, n + 1):
            if random.randint(0, 99) < 25:
                w = random.randint(-3, 5)
                edges.append((u, v, w))
                indeg[v] += 1

    print(n, len(edges))
    for i in range(1, n + 1):
        if indeg[i] == 0:
            c = random.randint(0, 5)
            u = 0
        else:
            c = 0
            u = random.randint(0, 5)
        print(c, u)

    for u, v, w in edges:
        print(u, v, w)


if __name__ == "__main__":
    main()
