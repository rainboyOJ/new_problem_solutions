#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    m = random.randint(1, 30)
    b = random.randint(1, 10)
    g = random.randint(1, 10)
    print(n, m, b, g)

    for _ in range(b):
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(l, r)

    for _ in range(g):
        l = random.randint(1, m)
        r = random.randint(l, m)
        print(l, r)


if __name__ == "__main__":
    main()
