#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 9)
    d = random.randint(1, 30)
    print(n, d)
    for _ in range(n):
        print(random.randint(1, 20), random.randint(1, 20))


if __name__ == "__main__":
    main()
