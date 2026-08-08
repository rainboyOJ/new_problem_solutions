#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    m = random.randint(1, 8)
    s = random.randint(1, 300)
    print(n, m, s)
    for _ in range(n):
        w = random.randint(1, 10)
        v = random.randint(1, 10)
        print(w, v)
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(l, r)


if __name__ == "__main__":
    main()
