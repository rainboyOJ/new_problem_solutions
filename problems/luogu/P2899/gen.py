#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 18)
    print(n)
    for i in range(2, n + 1):
        p = random.randint(1, i - 1)
        print(p, i)


if __name__ == "__main__":
    main()
