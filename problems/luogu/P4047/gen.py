#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 7)
    k = random.randint(2, n)

    used = set()
    points = []
    while len(points) < n:
        x = random.randint(0, 20)
        y = random.randint(0, 20)
        if (x, y) in used:
            continue
        used.add((x, y))
        points.append((x, y))

    print(n, k)
    for x, y in points:
        print(x, y)


if __name__ == "__main__":
    main()
