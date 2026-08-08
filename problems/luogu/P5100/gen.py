#!/usr/bin/env python3

import random


def main():
    h = random.randint(1, 5)
    w = random.randint(1, 5)
    a = random.randint(0, 5)
    b = random.randint(0, 5)
    c = random.randint(0, 5)
    n = random.randint(2, 5)

    pos = []
    for _ in range(n):
        x = random.randint(0, h)
        y = random.randint(0, w)
        pos.append((x, y))

    while pos[0] == pos[-1]:
        pos[-1] = (random.randint(0, h), random.randint(0, w))

    print(h, w)
    print(a, b, c)
    print(n)
    for x, y in pos:
        print(x, y)


if __name__ == "__main__":
    main()
