#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 12)
    m = random.randint(1, 12)
    x = random.randint(1, n)
    y = random.randint(1, m)
    print(n, m, x, y)


if __name__ == "__main__":
    main()
