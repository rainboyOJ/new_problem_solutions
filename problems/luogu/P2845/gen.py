#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 8)
    m = random.randint(1, n * n * 3)
    print(n, m)
    for _ in range(m):
        a = random.randint(1, n)
        b = random.randint(1, n)
        c = random.randint(1, n)
        d = random.randint(1, n)
        print(a, b, c, d)


if __name__ == "__main__":
    main()
