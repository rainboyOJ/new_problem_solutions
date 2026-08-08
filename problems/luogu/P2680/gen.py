#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 18)
    m = random.randint(1, 35)

    print(n, m)
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        w = random.randint(0, 20)
        print(parent, i, w)
    for _ in range(m):
        u = random.randint(1, n)
        v = random.randint(1, n)
        print(u, v)


if __name__ == "__main__":
    main()
