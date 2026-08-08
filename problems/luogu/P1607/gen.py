#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    k = random.randint(1, 8)
    n = random.randint(2, 8)
    c = random.randint(1, 5)

    print(k, n, c)
    for _ in range(k):
        s = random.randint(1, n - 1)
        e = random.randint(s + 1, n)
        m = random.randint(1, 6)
        print(s, e, m)


if __name__ == "__main__":
    main()
