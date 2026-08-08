#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    edges = []
    for u in range(1, n + 1):
        for v in range(u + 1, n + 1):
            if random.randint(0, 99) < 35:
                edges.append((u, v))

    print(n, len(edges))
    for _ in range(n):
        print(random.randint(1, 10))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
