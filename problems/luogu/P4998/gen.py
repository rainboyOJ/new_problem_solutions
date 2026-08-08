#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 20)
    k = random.randint(1, n - 1)
    arr = [random.randint(0, 20) for _ in range(n)]
    print(n, k)
    print(" ".join(map(str, arr)))


if __name__ == "__main__":
    main()
