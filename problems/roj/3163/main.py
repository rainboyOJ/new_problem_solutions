#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:58
# update_at: 2026-10-01 22:06

import sys
from itertools import accumulate

# 不可达状态的哨兵：真实得分 ≥ 0，而它沿一条链最多被加 41 次、每次至多 100 分，
# 远不足以翻正，所以在 max 比较里永远输给任何真实结果。
NEG = -10**9


def dp_row(prev_1: list[int], prev_2: list[int], prev_3: list[int], gains: list[int], seed: int) -> list[int]:
    """固定已用 1/2/3 卡的张数，推出「用 c4 张 4 卡」整行的最大得分。

    下标 c4 表示 4 卡用了 c4 张。同一状态无论最后用的是哪类卡，都停在同一个格子
    step = c1 + 2*c2 + 3*c3 + 4*c4，所以格子分是该状态的公共加项：
    - best 是分别少用一张 1/2/3 卡的三行在同一 c4 上的逐位 max；
    - 少用一张 4 卡的前驱就是本行的前一格，是沿 c4 串起来的链；
    - 因此 dp[c4] = max(best[c4], dp[c4-1]) + gains[c4]，用 accumulate 一次扫完；
    - seed 是虚拟前驱的分数：起点那一行给 0（起点分数在 gains[0] 里再加一次），
      其余行给 NEG。NEG 只需足够深（见模块级注释）。
    """
    best = map(max, prev_1, prev_2, prev_3)  # 三类卡分别作为最后一手
    row = accumulate(zip(best, gains), lambda acc, p: max(acc, p[0]) + p[1], initial=seed)
    return list(row)[1:]  # 丢掉 initial 多出来的那一项


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    board = [next(data) for _ in range(n)]

    counts = [0] * 5  # counts[v] = 写着数字 v 的卡片张数（1..4）
    for _ in range(m):
        counts[next(data)] += 1
    n1, n2, n3, n4 = counts[1:]

    dead_row = [NEG] * (n4 + 1)  # 某类卡已用完时，该方向的前驱行整行不可达
    prev_plane: list[list[list[int]]] | None = None  # dp 的 c1-1 平面，逐层滚动，省内存
    for c1 in range(n1 + 1):
        plane: list[list[list[int]]] = []
        for c2 in range(n2 + 1):
            line: list[list[int]] = []
            for c3 in range(n3 + 1):
                step = c1 + 2 * c2 + 3 * c3  # 已走格子数，也就是当前格的下标
                gains = board[step : step + 4 * n4 + 1 : 4]  # 本行各 c4 落到的格子分
                prev_a = prev_plane[c2][c3] if c1 else dead_row
                prev_b = plane[c2 - 1][c3] if c2 else dead_row
                prev_c = line[c3 - 1] if c3 else dead_row
                seed = 0 if step == 0 else NEG  # 只有起点 (0,0,0,c4) 有 0 分的虚拟前驱
                line.append(dp_row(prev_a, prev_b, prev_c, gains, seed))
            plane.append(line)
        prev_plane = plane

    print(prev_plane[n2][n3][n4])  # 用光全部卡片，落点必是第 n 格


if __name__ == "__main__":
    solve()
