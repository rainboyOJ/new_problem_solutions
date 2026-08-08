#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 80)
    now = 0
    print(n)
    for _ in range(n):
        now += random.randint(0, 10)
        typ = random.randint(0, 1)
        price = random.randint(1, 20)
        print(typ, price, now)


if __name__ == "__main__":
    main()
