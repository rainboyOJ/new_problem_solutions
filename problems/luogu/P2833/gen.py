#!/usr/bin/env python3

import random


def main():
    a = random.randint(-10, 10)
    b = random.randint(-10, 10)
    while a == 0 and b == 0:
        a = random.randint(-10, 10)
        b = random.randint(-10, 10)
    c = random.randint(-20, 20)
    x1 = random.randint(-10, 10)
    x2 = random.randint(-10, 10)
    y1 = random.randint(-10, 10)
    y2 = random.randint(-10, 10)
    print(a, b, c, x1, x2, y1, y2)


if __name__ == "__main__":
    main()
