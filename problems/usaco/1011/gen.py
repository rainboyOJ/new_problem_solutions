#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(3, 15)

    points = set()

    # 先放一个保证合法的直角三角形。
    ax = random.randint(-10, 10)
    ay = random.randint(-10, 10)
    dx = random.choice([-1, 1]) * random.randint(1, 10)
    dy = random.choice([-1, 1]) * random.randint(1, 10)

    points.add((ax, ay))
    points.add((ax + dx, ay))
    points.add((ax, ay + dy))

    while len(points) < n:
        points.add((random.randint(-10, 10), random.randint(-10, 10)))

    print(n)
    for x, y in points:
        print(x, y)


if __name__ == "__main__":
    main()
