#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 10)
    print(n)
    for _ in range(n):
        num = random.randint(1, 999)
        p = random.randint(0, 9)
        print(num * 10 + p)


if __name__ == "__main__":
    main()
