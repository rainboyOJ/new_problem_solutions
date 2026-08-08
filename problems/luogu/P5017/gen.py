#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 9)
    m = random.randint(1, 6)
    arr = [random.randint(0, 20) for _ in range(n)]

    print(n, m)
    print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
