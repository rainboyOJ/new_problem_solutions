#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 10)
    r = random.randint(1, 4)
    print(n, r)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        t = random.randint(0, 2)
        print(i, p, t)


if __name__ == "__main__":
    main()
