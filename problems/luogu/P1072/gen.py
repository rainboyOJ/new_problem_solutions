#!/usr/bin/env python3
import random
import math


def main():
    random.seed()
    t = random.randint(1, 8)
    print(t)
    for _ in range(t):
        a0 = random.randint(1, 50)
        a1 = random.randint(1, a0)
        while a0 % a1 != 0:
            a1 = random.randint(1, a0)

        b0 = random.randint(1, 50)
        b1 = random.randint(1, 50)
        while b1 % b0 != 0:
            b1 = random.randint(1, 50)

        print(a0, a1, b0, b1)


if __name__ == "__main__":
    main()
