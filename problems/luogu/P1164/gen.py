#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 14)
    money = random.randint(1, 40)
    prices = [random.randint(1, 20) for _ in range(n)]

    print(n, money)
    print(*prices)


if __name__ == "__main__":
    main()
