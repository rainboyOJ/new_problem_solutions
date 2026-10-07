#!/usr/bin/env python3

import random


def main():
    a = random.randint(-4, 4)
    b = random.randint(-4, 4)
    c = random.randint(-4, 4)
    d = random.randint(-4, 4)
    while a == 0 and b == 0 and c == 0 and d == 0:
        a = random.randint(-4, 4)
        b = random.randint(-4, 4)
        c = random.randint(-4, 4)
        d = random.randint(-4, 4)
    print(a, b, c, d)


if __name__ == "__main__":
    main()
