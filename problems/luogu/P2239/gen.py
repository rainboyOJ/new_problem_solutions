#!/usr/bin/env python3
import random


def main():
    n = random.randint(1, 30)
    i = random.randint(1, n)
    j = random.randint(1, n)
    print(n, i, j)


if __name__ == "__main__":
    main()
