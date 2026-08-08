#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 14)
    limit_w = random.randint(1, 30)
    print(n, limit_w)
    for _ in range(n):
        print(random.randint(1, limit_w))


if __name__ == "__main__":
    main()
