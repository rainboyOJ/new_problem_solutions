#!/usr/bin/env python3
import random


def gen_case():
    n = random.randint(3, 7)
    max_edges = min(10, n * (n - 1) // 2)
    m = random.randint(1, max_edges)

    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))
    random.shuffle(all_edges)
    chosen = all_edges[:m]

    return n, chosen


def main():
    random.seed()

    t = random.randint(1, 3)
    print(t)
    for _ in range(t):
        n, edges = gen_case()
        print(n, len(edges))
        for u, v in edges:
            print(u, v)


if __name__ == "__main__":
    main()
