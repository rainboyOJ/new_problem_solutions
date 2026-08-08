#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    q = random.randint(1, 50)

    print(n)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(p, i)

    print(q)
    for _ in range(q):
        l = random.randint(1, n)
        r = random.randint(l, n)
        k = random.randint(1, r - l + 1)
        print(l, r, k)


if __name__ == "__main__":
    main()
