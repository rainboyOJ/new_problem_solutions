#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 20)
    m = random.randint(0, min(60, n * n))
    print(n, m)
    for _ in range(m):
        u = random.randint(1, n)
        v = random.randint(1, n)
        print(u, v)

    s = random.randint(1, n)
    t = random.randint(1, n)
    while s == t:
        t = random.randint(1, n)
    print(s, t)


if __name__ == "__main__":
    main()
