#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 10)
    m = random.randint(1, 10)
    a = random.randint(1, min(5, n * m))
    b = random.randint(1, min(10, n * m))
    print(n, m, a, b)

    cells = [(i, j) for i in range(1, n + 1) for j in range(1, m + 1)]
    random.shuffle(cells)
    sources = cells[:a]
    for x, y in sources:
        print(x, y)

    for _ in range(b):
        x = random.randint(1, n)
        y = random.randint(1, m)
        print(x, y)


if __name__ == "__main__":
    main()
