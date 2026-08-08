#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 10)
    k = random.randint(1, 4)
    p = random.randint(0, 10)

    print(n, k, p)
    for _ in range(n):
        c = random.randint(0, k - 1)
        b = random.randint(0, 10)
        print(c, b)


if __name__ == "__main__":
    main()
