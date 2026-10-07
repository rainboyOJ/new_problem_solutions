#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))

    random.shuffle(all_edges)
    m = random.randint(0, len(all_edges))
    edges = all_edges[:m]

    print(n, m)
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
