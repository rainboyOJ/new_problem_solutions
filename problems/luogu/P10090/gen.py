#!/usr/bin/env python3
import random


def main():
    random.seed()
    t = random.randint(1, 10)
    print(t)
    for _ in range(t):
        n = random.randint(4, 15)
        a = random.randint(0, 25)
        b = random.randint(0, 25)
        print(n, a, b)


if __name__ == "__main__":
    main()
