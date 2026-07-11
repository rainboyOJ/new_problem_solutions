#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 40)
    cells = random.sample([(x, y) for x in range(0, 12) for y in range(0, 12)], n)
    print(n)
    for x, y in cells:
        print(x, y)


if __name__ == "__main__":
    main()
