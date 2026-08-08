#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 120)
    k = random.randint(1, 200)

    print(n, k)
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        print(parent, i)
    for _ in range(k):
        u = random.randint(1, n)
        v = random.randint(1, n)
        print(u, v)


if __name__ == "__main__":
    main()
