#!/usr/bin/env python3
import random


def knight_reachable(start, target, m):
    from collections import deque

    dx = [-1, 1, 2, -2, -1, 1, 2, -2]
    dy = [2, 2, 1, 1, -2, -2, -1, -1]

    dist = [[-1] * (m + 1) for _ in range(m + 1)]
    q = deque([start])
    dist[start[0]][start[1]] = 0

    while q:
        x, y = q.popleft()
        if (x, y) == target:
            return True
        for i in range(8):
            nx, ny = x + dx[i], y + dy[i]
            if nx <= 0 or ny <= 0 or nx > m or ny > m:
                continue
            if dist[nx][ny] != -1:
                continue
            dist[nx][ny] = dist[x][y] + 1
            q.append((nx, ny))
    return False


def main():
    random.seed()

    m = random.randint(4, 10)
    n = random.randint(1, 8)

    pts = []
    used = set()

    while len(pts) < n:
        x = random.randint(1, m)
        y = random.randint(1, m)
        if (x, y) in used:
            continue
        if pts and not knight_reachable(pts[0], (x, y), m):
            continue
        used.add((x, y))
        pts.append((x, y))

    print(n, m)
    for x, y in pts:
        print(x, y)


if __name__ == "__main__":
    main()
