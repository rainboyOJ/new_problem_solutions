#!/usr/bin/env python3
import random


def main():
    random.seed()

    max_coord = random.randint(1, 8)
    n = random.randint(1, 12)
    k = random.randint(1, n)
    print(n, k)

    for _ in range(n):
        x1 = random.randint(0, max_coord - 1)
        x2 = random.randint(x1 + 1, max_coord)
        y1 = random.randint(0, max_coord - 1)
        y2 = random.randint(y1 + 1, max_coord)
        print(x1, y1, x2, y2)


if __name__ == "__main__":
    main()
