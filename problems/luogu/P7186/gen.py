#!/usr/bin/env python3
import random


def main():
    n = random.randint(2, 8)
    k = random.randint(1, 8)
    print(n, k)
    for _ in range(k):
        x = random.randint(1, n * n)
        r = random.randint(1, n)
        c = random.randint(1, n)
        print(x, r, c)


if __name__ == "__main__":
    main()
