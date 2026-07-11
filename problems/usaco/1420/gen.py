#!/usr/bin/env python3
import random


def main():
    random.seed()
    w = random.randint(1, 20)
    h = random.randint(1, 20)
    n = random.randint(1, 30)
    p = 4

    def random_point():
        side = random.randint(0, 3)
        if side == 0:
            return random.randint(0, w), 0
        if side == 1:
            return w, random.randint(0, h)
        if side == 2:
            return random.randint(0, w), h
        return 0, random.randint(0, h)

    print(n, p)
    print(0, 0)
    print(w, 0)
    print(w, h)
    print(0, h)
    for _ in range(n):
        x1, y1 = random_point()
        x2, y2 = random_point()
        print(x1, y1, x2, y2)


if __name__ == "__main__":
    main()
