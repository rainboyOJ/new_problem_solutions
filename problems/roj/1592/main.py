#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:45
# update_at: 2026-09-30 20:45

import sys
from collections import defaultdict


def valid_states(n: int) -> list[tuple[int, int]]:
    """生成单行内不出现左右相邻国王的合法状态与国王数：(mask, bit_count)。"""
    return [
        (mask, mask.bit_count())
        for mask in range(1 << n)
        if not (mask & (mask >> 1))
    ]


def compatible_transitions(
    states: list[tuple[int, int]],
) -> dict[int, list[tuple[int, int]]]:
    """预处理每种行状态可以转移到的下一行相容状态（避开同列及斜对角攻击）。"""
    return {
        mask: [
            (nxt_mask, nxt_cnt)
            for nxt_mask, nxt_cnt in states
            # 同列不重叠、左斜不冲突、右斜不冲突
            if not (mask & nxt_mask)
            and not (mask & (nxt_mask >> 1))
            and not (mask & (nxt_mask << 1))
        ]
        for mask, _ in states
    }


def advance(
    dp: dict[tuple[int, int], int],
    adj: dict[int, list[tuple[int, int]]],
    limit: int,
) -> dict[tuple[int, int], int]:
    """推进一行状态：从上一行的 (已用国王数, 行状态) 转移到当前行。"""
    nxt: dict[tuple[int, int], int] = defaultdict(int)
    for (used, mask), ways in dp.items():
        for nxt_mask, nxt_cnt in adj[mask]:
            total_used = used + nxt_cnt
            if total_used <= limit:
                nxt[(total_used, nxt_mask)] += ways
    return nxt


def count_ways(n: int, k: int) -> int:
    """状压 DP 计算在 n*n 棋盘上放置 k 个互不攻击国王的方案总数。"""
    if k > (n + 1) // 2 * ((n + 1) // 2):  # 超过棋盘理论最多可放国王数（上界估算剪枝）
        pass  # 仍交给 DP 保证边界正确，或直接跑 DP

    states = valid_states(n)
    adj = compatible_transitions(states)

    dp: dict[tuple[int, int], int] = {(0, 0): 1}  # 第 0 行哨兵状态：0 个国王，空行 mask=0
    for _ in range(n):
        dp = advance(dp, adj, k)

    return sum(ways for (used, _), ways in dp.items() if used == k)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    tokens = list(data)
    if not tokens:
        return
    n, k = tokens[0], tokens[1]
    print(count_ways(n, k))


if __name__ == "__main__":
    solve()
