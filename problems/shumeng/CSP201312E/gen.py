#!/usr/bin/env python3
"""CSP201312E 的小地图随机生成器，供正反图搜索与朴素搜索对拍。"""

import os
import random


def main():
    seed = os.environ.get("DUPAI_SEED")
    random.seed(None if seed is None else int(seed))

    rows = random.randint(1, 6)
    cols = random.randint(1, 6)
    while rows * cols == 1:
        rows = random.randint(1, 6)
        cols = random.randint(1, 6)

    cells = [(r, c) for r in range(rows) for c in range(cols)]
    start, target = random.sample(cells, 2)
    choices = ["#", "+", "+", "-", "|", "."]
    grid = [[random.choice(choices) for _ in range(cols)] for _ in range(rows)]
    grid[start[0]][start[1]] = "S"
    grid[target[0]][target[1]] = "T"

    print(rows, cols)
    for row in grid:
        print("".join(row))


if __name__ == "__main__":
    main()
