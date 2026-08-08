#!/usr/bin/env python3

import random


def main():
    n = random.randint(1, 7)
    m = random.randint(1, 7)
    total = n * m
    k = random.randint(0, total - 1)
    cells = [(i, j) for i in range(1, n + 1) for j in range(1, m + 1)]
    random.shuffle(cells)
    blocked = cells[:k]

    print(n, m, k)
    for x, y in blocked:
        print(x, y)


if __name__ == "__main__":
    main()
