#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 5)
    print(n)
    for _ in range(n):
        k = random.randint(1, 5)
        arr = [random.randint(1, 10) for _ in range(k)]
        print(*arr, -1)


if __name__ == "__main__":
    main()
