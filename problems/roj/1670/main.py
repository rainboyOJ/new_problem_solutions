#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def next_end_state(x: int, l: int, r: int, is_left: bool) -> int:
    """根据子区间两侧必败态阈值及新堆石子数推导新端点的必败态阈值。"""
    if x == (r if is_left else l):
        return 0
    if (x > l and x > r) or (x < l and x < r):
        return x
    return x - 1 if (r < x < l if is_left else l < x < r) else x + 1


def is_first_win(piles: list[int]) -> int:
    """判断当前石子序列是否存在先手必胜策略：1 为必胜，0 为必败。"""
    n = len(piles)
    if n == 1:
        return 1

    # L[i][j] 与 R[i][j] 表示给区间加左/右侧石子使其成为必败态所需的石子数
    # 下标 1-based 便于对应原始区间 [i, j]
    l_dp = [[0] * (n + 1) for _ in range(n + 1)]
    r_dp = [[0] * (n + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        l_dp[i][i] = r_dp[i][i] = piles[i - 1]

    for length in range(2, n):
        for i in range(1, n - length + 2):
            j = i + length - 1
            l_dp[i][j] = next_end_state(piles[j - 1], l_dp[i][j - 1], r_dp[i][j - 1], is_left=True)
            r_dp[i][j] = next_end_state(piles[i - 1], l_dp[i + 1][j], r_dp[i + 1][j], is_left=False)

    target = next_end_state(piles[n - 1], l_dp[2][n - 1], r_dp[2][n - 1], is_left=True) if n > 2 else piles[n - 1]
    return 0 if piles[0] == target else 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    cases = next(data, 0)

    for _ in range(cases):
        pile_count = next(data)
        stones = [next(data) for _ in range(pile_count)]
        out.append(str(is_first_win(stones)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
