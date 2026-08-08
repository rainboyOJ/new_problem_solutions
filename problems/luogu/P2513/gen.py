#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 8)
    max_inv = n * (n - 1) // 2
    k = random.randint(0, max_inv)
    print(n, k)


if __name__ == "__main__":
    main()
