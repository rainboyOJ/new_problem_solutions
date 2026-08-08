#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    print(n)
    for _ in range(n):
        iq = random.randint(-10, 10)
        eq = random.randint(-10, 10)
        print(iq, eq)


if __name__ == "__main__":
    main()
