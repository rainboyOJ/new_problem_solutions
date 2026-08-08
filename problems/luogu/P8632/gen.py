#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 40)
    L = random.randint(1, 40)

    pos = sorted(random.randint(0, L) for _ in range(n))
    print(n, L)
    for x in pos:
        print(x, random.randint(0, 10))


if __name__ == "__main__":
    main()
