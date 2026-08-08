#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    k = random.randint(1, 8)

    arr = [random.randint(-6, 6) for _ in range(n)]
    arr.sort()

    print(n, k)
    print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
