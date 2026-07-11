#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 8)
    print(n)
    for _ in range(n):
        row = [random.randint(95, 105) for _ in range(n)]
        print(*row)


if __name__ == "__main__":
    main()
