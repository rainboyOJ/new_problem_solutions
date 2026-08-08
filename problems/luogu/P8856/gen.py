#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    c = random.randint(2, 12)
    s = random.randint(1, 10)
    r = random.randint(1, 30)
    print(c, s, r)
    for _ in range(r):
        o = random.randint(1, c - 1)
        d = random.randint(o + 1, c)
        n = random.randint(1, 10)
        print(o, d, n)


if __name__ == "__main__":
    main()
