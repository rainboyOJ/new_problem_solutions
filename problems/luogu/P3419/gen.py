#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    k = random.randint(1, n)
    p = random.randint(1, 10)
    print(n, k, p)
    for _ in range(p):
        print(random.randint(1, n))


if __name__ == "__main__":
    main()
