#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 40)
    k = random.randint(0, n - 1)
    print(n, k)


if __name__ == "__main__":
    main()
