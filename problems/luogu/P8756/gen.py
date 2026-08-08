#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 4)
    m = random.randint(1, 6)
    k = random.randint(1, min(8, n * m))
    print(n, m, k)


if __name__ == "__main__":
    main()
