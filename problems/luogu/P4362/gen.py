#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(2, 12)
    k = random.randint(1, n - 1)
    m = random.randint(2, n - k + 1)
    print(n, m, k)

    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        w = random.randint(0, 20)
        print(p, i, w)


if __name__ == "__main__":
    main()
