#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 30)
    all_edges = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            all_edges.append((i, j))

    random.shuffle(all_edges)
    m = random.randint(0, min(len(all_edges), 60))

    used = set()
    points = []
    while len(points) < n:
        x = random.randint(1, 200)
        y = random.randint(1, 200)
        if (x, y) in used:
            continue
        used.add((x, y))
        points.append((x, y))

    print(n, m)
    for x, y in points:
        print(x, y)
    for i in range(m):
        print(all_edges[i][0], all_edges[i][1])


if __name__ == "__main__":
    main()
