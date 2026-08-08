#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 200)
    m = random.randint(1, 300)
    root = random.randint(1, n)

    edges = []
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        edges.append((parent, i))

    print(n, m, root)
    for u, v in edges:
        print(u, v)
    for _ in range(m):
        x = random.randint(1, n)
        y = random.randint(1, n)
        print(x, y)


if __name__ == "__main__":
    main()
