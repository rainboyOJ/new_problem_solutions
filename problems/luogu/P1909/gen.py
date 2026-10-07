#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 1000)
    print(n)
    for _ in range(3):
        cnt = random.randint(1, 100)
        price = random.randint(1, 1000)
        print(cnt, price)


if __name__ == "__main__":
    main()
