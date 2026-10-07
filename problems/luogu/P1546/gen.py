#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 6)
    a = [[0] * n for _ in range(n)]

    for i in range(n):
        for j in range(i + 1, n):
            w = random.randint(1, 20)
            a[i][j] = w
            a[j][i] = w

    print(n)
    for i in range(n):
        print(*a[i])


if __name__ == "__main__":
    main()
