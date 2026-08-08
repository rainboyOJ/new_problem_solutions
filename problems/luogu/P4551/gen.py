#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 200)
    print(n)
    for i in range(2, n + 1):
        parent = random.randint(1, i - 1)
        w = random.randint(0, (1 << 20) - 1)
        print(parent, i, w)


if __name__ == "__main__":
    main()
