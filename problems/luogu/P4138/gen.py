#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 14)
    print(n)
    for _ in range(n):
        a = random.randint(0, n)
        b = random.randint(-20, 20)
        print(a, b)


if __name__ == "__main__":
    main()
