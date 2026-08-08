#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    t = random.randint(1, 7)
    max_p = random.randint(1, 6)
    w = random.randint(0, max(0, t - 1))
    print(t, max_p, w)
    for _ in range(t):
        ap = random.randint(1, 15)
        bp = random.randint(1, ap)
        a_s = random.randint(1, max_p)
        b_s = random.randint(1, max_p)
        print(ap, bp, a_s, b_s)


if __name__ == "__main__":
    main()
