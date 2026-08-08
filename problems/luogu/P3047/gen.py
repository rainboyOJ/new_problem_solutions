#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 16)
    k = random.randint(1, 5)
    print(n, k)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(i, p)
    for i in range(1, n + 1):
        print(random.randint(0, 10))


if __name__ == "__main__":
    main()
