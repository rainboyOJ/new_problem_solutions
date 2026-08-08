#!/usr/bin/env python3
import random
from collections import deque


def reachable(grid):
    r = len(grid)
    c = len(grid[0])
    if grid[0][0] == "*" or grid[r - 1][c - 1] == "*":
        return False
    q = deque([(0, 0)])
    vis = [[False] * c for _ in range(r)]
    vis[0][0] = True
    while q:
        x, y = q.popleft()
        if (x, y) == (r - 1, c - 1):
            return True
        for dx, dy in ((0, 1), (1, 0), (0, -1), (-1, 0)):
            nx, ny = x + dx, y + dy
            if 0 <= nx < r and 0 <= ny < c and not vis[nx][ny] and grid[nx][ny] == ".":
                vis[nx][ny] = True
                q.append((nx, ny))
    return False


def main():
    random.seed()
    while True:
        r = random.randint(2, 8)
        c = random.randint(2, 8)
        grid = []
        for _ in range(r):
            row = []
            for _ in range(c):
                row.append("." if random.randint(0, 99) < 70 else "*")
            grid.append(row)
        grid[0][0] = "."
        grid[r - 1][c - 1] = "."
        if reachable(grid):
            print(r, c)
            for row in grid:
                print("".join(row))
            return


if __name__ == "__main__":
    main()
