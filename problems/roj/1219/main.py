#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:26
# update_at: 2026-09-30 00:26

import sys
from functools import cache

MOVES = ((1, 2), (1, -2), (-1, 2), (-1, -2), (2, 1), (2, -1), (-2, 1), (-2, -1))  # 马走日的 8 个日字方向


@cache
def neighbors(n: int, m: int) -> tuple[tuple[int, ...], ...]:
    """nbrs[pos]：n×m 棋盘上马从编号 pos 的格子一步可达的格子编号表（越界已滤掉）。

    起点不同但棋盘相同时多组数据可复用同一张表，所以按 (n, m) 做缓存。
    """
    return tuple(
        tuple(
            (r + dr) * m + (c + dc)
            for dr, dc in MOVES
            if 0 <= r + dr < n and 0 <= c + dc < m
        )
        for r in range(n) for c in range(m)
    )


def count_tours(n: int, m: int, x: int, y: int) -> int:
    """统计从 (x, y) 出发、马走日且不重访任何格子的棋盘全遍历路径条数。

    棋盘压成位图：格子 (r, c) 编号为 r*m+c，visited 第 pos 位为 1 表示已访问。
    """
    nbrs = neighbors(n, m)
    total = n * m

    def dfs(pos: int, visited: int, left: int) -> int:
        """从 pos 出发、还有 left 个格子未访问时的完整遍历条数。"""
        if left == 0:
            return 1                                   # 所有格子恰好各走一次
        cnt = 0
        for nxt in nbrs[pos]:
            free = not visited >> nxt & 1              # 移位后取位：目标格还没走过
            if free:
                cnt += dfs(nxt, visited | 1 << nxt, left - 1)
        return cnt

    start = x * m + y
    return dfs(start, 1 << start, total - 1)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m, x, y = next(data), next(data), next(data), next(data)
        out.append(str(count_tours(n, m, x, y)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
