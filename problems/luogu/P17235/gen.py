#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 5)
    print(t)
    for _ in range(t):
        n = random.randint(1, 8)
        all_edges = [(i, j) for i in range(1, n + 1) for j in range(i + 1, n + 1)]
        random.shuffle(all_edges)
        m = random.randint(0, min(12, len(all_edges)))
        edges = all_edges[:m]
        k = random.randint(1, n)
        print(n, m, k)
        for u, v in edges:
            if random.randint(0, 1):
                u, v = v, u
            print(u, v)


if __name__ == "__main__":
    main()
