#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 7)
    cells = []
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            cells.append((i, j))

    random.shuffle(cells)
    q = random.randint(1, n * n)
    dirs = ["L", "R", "U", "D"]

    print(n, q)
    for i in range(q):
        r, c = cells[i]
        print(r, c, random.choice(dirs))


if __name__ == "__main__":
    main()
