#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 14)
    print(n)
    for _ in range(n):
        l = random.randint(0, 30)
        r = random.randint(l + 1, 40)
        print(l, r)


if __name__ == "__main__":
    main()
