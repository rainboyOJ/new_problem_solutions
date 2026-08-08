#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 10)
    m = random.randint(1, n)
    print(n, m)

    for _ in range(n):
        l = random.randint(0, 10)
        r = random.randint(l, 12)
        print(l, r)


if __name__ == "__main__":
    main()
