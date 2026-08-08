from functools import cache
import sys


def read_all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


n, m, horse_x, horse_y = read_all_ints()
blocked = {
    (horse_x + dx, horse_y + dy)
    for dx, dy in [
        (0, 0), (1, 2), (2, 1), (2, -1), (1, -2),
        (-1, -2), (-2, -1), (-2, 1), (-1, 2),
    ]
    if 0 <= horse_x + dx <= n and 0 <= horse_y + dy <= m
}


@cache
def dfs(x, y):
    if (x, y) in blocked:
        return 0
    if x == n and y == m:
        return 1
    return (dfs(x + 1, y) if x < n else 0) + (dfs(x, y + 1) if y < m else 0)


print(dfs(0, 0))
