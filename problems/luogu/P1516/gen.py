#!/usr/bin/env python3

import random


def main():
    L = random.randint(2, 100)
    x = random.randint(0, L - 1)
    y = random.randint(0, L - 1)
    while y == x:
        y = random.randint(0, L - 1)
    m = random.randint(1, 20)
    n = random.randint(1, 20)
    print(x, y, m, n, L)


if __name__ == "__main__":
    main()
