#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    k = random.randint(1, n)
    print(n, k)
    for i in range(1, n + 1):
        row = [random.randint(0, 30) for _ in range(i)]
        print(*row)


if __name__ == "__main__":
    main()
