#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 12)
    k = random.randint(1, n)
    print(n, k)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(p, i)


if __name__ == "__main__":
    main()
