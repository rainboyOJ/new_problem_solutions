#!/usr/bin/env python3

import random


def main():
    n = random.randint(1, 10)
    m = random.randint(1, 20)
    k = random.randint(1, n)
    arr = [random.randint(1, m) for _ in range(n)]
    print(n, m, k)
    print(*arr)


if __name__ == "__main__":
    main()
