#!/usr/bin/env python3
import random


def main():
    random.seed()
    p = random.randint(2, 7)
    s = random.randint(1, p - 1)

    used = set()
    points = []
    while len(points) < p:
        x = random.randint(0, 50)
        y = random.randint(0, 50)
        if (x, y) in used:
            continue
        used.add((x, y))
        points.append((x, y))

    print(s, p)
    for x, y in points:
        print(x, y)


if __name__ == "__main__":
    main()
