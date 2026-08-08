#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 8)
    m = random.randint(1, 10)
    print(n, m)
    for _ in range(n):
        print(random.randint(1, 4))
    for _ in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        print(l, r)


if __name__ == "__main__":
    main()
