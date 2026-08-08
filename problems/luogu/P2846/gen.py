#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 30)
    m = random.randint(1, 60)
    print(n, m)
    for _ in range(m):
        op = random.randint(0, 1)
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(op, l, r)


if __name__ == "__main__":
    main()
