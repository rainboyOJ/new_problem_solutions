#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 9)
    k = random.randint(1, n)
    p = random.randint(2, 1000)
    print(n, k, p)


if __name__ == "__main__":
    main()
