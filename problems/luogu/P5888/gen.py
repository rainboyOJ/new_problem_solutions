#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(0, 7)
    max_k = min(n * (n - 1), 12)
    k = random.randint(0, max_k)
    print(n, m, k)

    all_edges = []
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if i != j:
                all_edges.append((i, j))
    random.shuffle(all_edges)
    for i in range(k):
        a, b = all_edges[i]
        print(a, b)


if __name__ == "__main__":
    main()
