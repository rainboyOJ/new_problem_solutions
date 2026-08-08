#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 9)
    print(n)
    for i in range(2, n + 1):
        print(random.randint(1, i - 1))


if __name__ == "__main__":
    main()
