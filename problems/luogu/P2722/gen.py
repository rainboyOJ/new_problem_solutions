#!/usr/bin/env python3
import random


def main():
    random.seed()

    n = random.randint(1, 8)
    t = random.randint(1, 30)
    items = []
    for _ in range(n):
        points = random.randint(1, 30)
        cost = random.randint(1, t)
        items.append((points, cost))

    print(t, n)
    for points, cost in items:
        print(points, cost)


if __name__ == "__main__":
    main()
