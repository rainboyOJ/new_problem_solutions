#!/usr/bin/env python3
import random


def main():
    m = random.randint(2, 18)
    total = random.randint(2, min(m * m + 5, 80))

    points = {(1, 1), (m, m)}
    while len(points) < min(total, m * m):
        points.add((random.randint(1, m), random.randint(1, m)))

    arr = list(points)
    extra = total - len(arr)
    for _ in range(extra):
        arr.append(random.choice(arr))

    random.shuffle(arr)

    print(len(arr), m)
    for x, y in arr:
        v = random.randint(1, 30)
        print(x, y, v)


if __name__ == "__main__":
    main()
