#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 12)
    m = random.randint(1, 40)
    print(n, m)

    for _ in range(m):
        op = random.randint(1, 2)
        x = random.randint(1, n)
        y = random.randint(1, n)
        print(op, x, y)


if __name__ == "__main__":
    main()
