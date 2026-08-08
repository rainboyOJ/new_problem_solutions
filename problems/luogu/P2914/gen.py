#!/usr/bin/env python3

import random


def random_point(used):
    while True:
        x = random.randint(0, 20)
        y = random.randint(0, 20)
        if (x, y) not in used:
            used.add((x, y))
            return x, y


def main():
    n = random.randint(2, 8)
    limit_len = random.randint(2, 10)

    used = set()
    pts = [None]
    for _ in range(n):
        pts.append(random_point(used))

    pairs = []
    for i in range(1, n + 1):
        for j in range(i + 1, n + 1):
            pairs.append((i, j))

    random.shuffle(pairs)
    w = random.randint(1, max(1, min(len(pairs), n + 2)))
    wires = pairs[:w]

    print(n, w)
    print(f"{limit_len:.1f}")
    for i in range(1, n + 1):
        print(pts[i][0], pts[i][1])
    for u, v in wires:
        print(u, v)


if __name__ == "__main__":
    main()
