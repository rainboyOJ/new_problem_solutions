#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 14)
    edges = []
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        edges.append((p, i))
    print(n, n - 1)
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
