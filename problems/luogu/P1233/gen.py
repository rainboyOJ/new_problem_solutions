#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 10)
    print(n)
    for _ in range(n):
        l = random.randint(1, 12)
        w = random.randint(1, 12)
        print(l, w)


if __name__ == "__main__":
    main()
