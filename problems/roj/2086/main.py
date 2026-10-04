#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import itertools
import math
import sys


def count_completions(n: int, p: tuple[int, ...]) -> int:
    """计算第 2 行固定为 p 时，剩余单元格的合法填充方案数。"""
    all_mask = (1 << n) - 1
    row_mask = [1 << r for r in range(n)]
    col_mask = [1 << c for c in range(n)]
    row_mask[0] = col_mask[0] = all_mask  # 第 1 行与第 1 列各填满了 0..n-1

    for c, v in enumerate(p, 1):
        row_mask[1] |= 1 << v
        col_mask[c] |= 1 << v

    def dfs(r: int, c: int) -> int:
        if r == n - 1:
            return 1
        nr, nc = (r, c + 1) if c + 1 < n else (r + 1, 1)
        avail = all_mask & ~(row_mask[r] | col_mask[c])
        cnt = 0
        while avail:
            low = avail & -avail
            avail ^= low
            row_mask[r] |= low
            col_mask[c] |= low
            cnt += dfs(nr, nc)
            row_mask[r] ^= low
            col_mask[c] ^= low
        return cnt

    return dfs(2, 1)


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    n = int(lines[0])
    if n <= 2:
        print(1)
        return

    rem = [0] + list(range(2, n))
    types: dict[tuple[int, ...], tuple[tuple[int, ...], int]] = {}

    for p in itertools.permutations(rem):
        if any(c == v for c, v in enumerate(p, 1)):
            continue
        full_p = (1, *p)
        vis, cycles = [False] * n, []
        for i in range(n):
            if not vis[i]:
                cur, length = i, 0
                while not vis[cur]:
                    vis[cur] = True
                    cur = full_p[cur]
                    length += 1
                cycles.append(length)
        key = tuple(sorted(cycles))
        types[key] = (p, types.get(key, (p, 0))[1] + 1)

    reduced_count = sum(count_completions(n, rep) * cnt for rep, cnt in types.values())
    print(reduced_count * math.factorial(n - 1))


if __name__ == "__main__":
    solve()
