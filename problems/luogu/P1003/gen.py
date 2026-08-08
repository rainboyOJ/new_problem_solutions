#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(0, 30)
    rects = []
    for _ in range(n):
        a = random.randint(0, 20)
        b = random.randint(0, 20)
        g = random.randint(0, 10)
        k = random.randint(0, 10)
        rects.append((a, b, g, k))
    x = random.randint(0, 30)
    y = random.randint(0, 30)
    print(n)
    for item in rects:
        print(*item)
    print(x, y)


if __name__ == "__main__":
    main()
