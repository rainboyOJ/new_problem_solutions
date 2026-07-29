#!/usr/bin/env python3
from collections import deque
from typing import List


class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        q = deque()
        fresh = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 2:
                    q.append((i, j))
                elif grid[i][j] == 1:
                    fresh += 1
        mins = 0
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        while q and fresh:
            mins += 1
            for _ in range(len(q)):
                x, y = q.popleft()
                for dx, dy in dirs:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 1:
                        grid[nx][ny] = 2
                        fresh -= 1
                        q.append((nx, ny))
        return -1 if fresh else mins


def main():
    m, n = map(int, input().split())
    g = [list(map(int, input().split())) for _ in range(m)]
    print(Solution().orangesRotting(g))


if __name__ == "__main__":
    main()
