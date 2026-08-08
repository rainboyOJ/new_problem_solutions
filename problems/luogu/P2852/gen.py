#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 60)
    k = random.randint(2, n)
    alphabet = random.randint(1, 8)

    print(n, k)
    for _ in range(n):
        print(random.randint(0, alphabet))


if __name__ == "__main__":
    main()
