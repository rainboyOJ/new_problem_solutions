#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    max_n = 8
    max_t = 5
    if len(sys.argv) >= 2:
        max_n = int(sys.argv[1])
    if len(sys.argv) >= 3:
        max_t = int(sys.argv[2])

    t = random.randint(1, max_t)
    print(t)
    for _ in range(t):
        n = random.randint(2, max_n)
        print(n)
        arr = []
        for _ in range(n):
            arr.append(random.randint(1, n))
        print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
