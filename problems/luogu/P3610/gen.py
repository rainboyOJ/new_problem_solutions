#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(2, 8)
    print(n)
    grid = [["E"] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if (i, j) in [(n - 1, 0), (0, n - 1)]:
                continue
            if random.random() < 0.2:
                grid[i][j] = "H"
    for row in grid:
        print("".join(row))


if __name__ == "__main__":
    main()
