#!/usr/bin/env python3
import random
import sys


def main():
    if len(sys.argv) > 1:
        random.seed(int(sys.argv[1]))
    else:
        random.seed()

    n = random.randint(1, 5)
    m = random.randint(1, 5)
    k = random.randint(1, 4)

    grid = [["." for _ in range(m)] for _ in range(n)]
    for i in range(n):
        for j in range(m):
            if random.randint(1, 100) <= 20:
                grid[i][j] = "x"

    empty_cells = []
    for i in range(n):
        for j in range(m):
            if grid[i][j] == ".":
                empty_cells.append((i + 1, j + 1))

    if not empty_cells:
        grid[0][0] = "."
        empty_cells.append((1, 1))

    start_x, start_y = random.choice(empty_cells)

    print(n, m, start_x, start_y, k)
    for i in range(n):
        print("".join(grid[i]))

    current = 1
    for _ in range(k):
        length = random.randint(1, 3)
        direction = random.randint(1, 4)
        print(current, current + length - 1, direction)
        current += length


if __name__ == "__main__":
    main()
