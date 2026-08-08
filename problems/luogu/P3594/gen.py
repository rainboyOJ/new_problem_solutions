#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 25)
    d = random.randint(1, n)
    arr = [random.randint(1, 20) for _ in range(n)]
    total = sum(arr)
    p = random.randint(0, total)

    print(n, p, d)
    print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
