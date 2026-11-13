#!/usr/bin/env python3
from collections import deque
import sys


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)

    n = int(next(it))
    m = int(next(it))
    r = int(next(it)) - 1
    c = int(next(it)) - 1
    max_l = int(next(it))
    max_r = int(next(it))

    grid = [next(it) for _ in range(n)]

    INF = 10**9
    dist = [[INF] * m for _ in range(n)]
    dist[r][c] = 0

    q = deque([(r, c)])
    dirs = ((-1, 0, 0), (1, 0, 0), (0, 1, 0), (0, -1, 1))

    while q:
        cx, cy = q.popleft()
        d = dist[cx][cy]

        for dx, dy, w in dirs:
            nx = cx + dx
            ny = cy + dy
            if 0 <= nx < n and 0 <= ny < m and grid[nx][ny] == ".":
                if dist[nx][ny] > d + w:
                    dist[nx][ny] = d + w
                    if w == 0:
                        q.appendleft((nx, ny))
                    else:
                        q.append((nx, ny))

    ans = 0
    for i in range(n):
        row_dist = dist[i]
        for j in range(m):
            L = row_dist[j]
            if L <= max_l:
                R = L + (j - c)
                if R <= max_r:
                    ans += 1

    print(ans)


if __name__ == "__main__":
    solve()
