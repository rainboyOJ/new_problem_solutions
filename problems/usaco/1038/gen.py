#!/usr/bin/env python3
import random


def build_runs(points):
    runs = []
    start = points[0]
    last = points[0]
    for x in points[1:]:
        if x == last + 1:
            last = x
        else:
            runs.append((start, last))
            start = last = x
    runs.append((start, last))
    return runs


def main():
    random.seed()
    while True:
        points = []
        for x in range(0, 21):
            if random.random() < 0.45:
                points.append(x)
        if len(points) >= 2 and len(points) <= 20:
            break

    runs = build_runs(points)
    n = random.randint(2, min(8, len(points)))
    print(n, len(runs))
    for l, r in runs:
        print(l, r)


if __name__ == "__main__":
    main()
