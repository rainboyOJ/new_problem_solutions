#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 14)
    detect = random.randint(1, 20)
    money = random.randint(1, 20)

    print(n, detect, money)
    for _ in range(n):
        a = random.randint(1, 20)
        b = random.randint(1, 12)
        c = random.randint(1, 12)
        print(a, b, c)


if __name__ == "__main__":
    main()
