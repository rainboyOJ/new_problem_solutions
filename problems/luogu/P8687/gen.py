#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 12)
    m = random.randint(1, 8)
    k = random.randint(1, m)
    print(n, m, k)
    for _ in range(n):
        arr = [random.randint(1, m) for _ in range(k)]
        print(*arr)


if __name__ == "__main__":
    main()
