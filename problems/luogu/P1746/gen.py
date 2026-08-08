#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 6)
    print(n)

    grid = []
    for _ in range(n):
        row = []
        for _ in range(n):
            row.append("1" if random.randint(1, 100) <= 35 else "0")
        grid.append(row)

    x1 = random.randint(1, n)
    y1 = random.randint(1, n)
    x2 = random.randint(1, n)
    y2 = random.randint(1, n)
    grid[x1 - 1][y1 - 1] = "0"
    grid[x2 - 1][y2 - 1] = "0"

    for row in grid:
        print("".join(row))
    print(x1, y1, x2, y2)


if __name__ == "__main__":
    main()
