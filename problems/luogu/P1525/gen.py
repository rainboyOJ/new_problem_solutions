#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 12)
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))

    random.shuffle(all_edges)
    max_m = min(len(all_edges), 40)
    m = random.randint(0, max_m)
    chosen = all_edges[:m]

    print(n, m)
    for u, v in chosen:
        w = random.randint(1, 1000)
        print(u, v, w)


if __name__ == "__main__":
    main()
