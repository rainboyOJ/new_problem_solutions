#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 12)
    m = random.randint(0, min(n - 1, 5))
    print(n, m)
    for _ in range(n):
        print(random.randint(1, 20))


if __name__ == "__main__":
    main()
