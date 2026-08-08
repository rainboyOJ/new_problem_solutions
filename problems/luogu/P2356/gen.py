#!/usr/bin/env python3
import random


def main():
    random.seed()
    n = random.randint(1, 20)
    grid = []
    zero_cnt = 0
    for _ in range(n):
        row = []
        for _ in range(n):
            if random.random() < 0.25:
                row.append(0)
                zero_cnt += 1
            else:
                row.append(random.randint(1, 9))
        grid.append(row)
    if zero_cnt == 0:
        x = random.randrange(n)
        y = random.randrange(n)
        grid[x][y] = 0
    print(n)
    for row in grid:
        print(*row)


if __name__ == "__main__":
    main()
