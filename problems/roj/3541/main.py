#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02
# update_at: 2026-10-02

import sys

INF = 10**9  # 不可达代价：石子至多 100 块，INF 远大于任何合法答案


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    length = next(data)                                   # 桥长 L
    min_jump, max_jump, stone_count = next(data), next(data), next(data)
    stones = sorted(next(data) for _ in range(stone_count))

    # S == T：每次跳固定距离，路径被唯一确定，青蛙必踩所有 S 的倍数点
    if min_jump == max_jump:
        print(sum(1 for pos in stones if pos % min_jump == 0))
        return

    # 无石子长段的 DP 值超过 cap 后恒定（推导见题解），每段截到 cap 即可
    period = max_jump - min_jump                          # T - S，窗口增长量
    lead = (2 * max_jump - 1 + period - 1) // period      # ceil((2T-1)/(T-S))
    cap = 1 + max_jump + max_jump * lead                  # B = H + T

    # 截断 = 把该点及之后的整体左移，等价于对「原始间距」逐段取 min(gap, cap)
    crossed: list[int] = []
    prev_orig = new_pos = 0
    for pos in stones + [length]:
        new_pos += min(pos - prev_orig, cap)
        crossed.append(new_pos)
        prev_orig = pos

    bridge = crossed[-1]                                  # 压缩后的桥长 L'
    has_stone = set(crossed[:-1])

    # 逐点 DP：dp[i] = 窗口 [i-T, i-S] 的最小代价 + 本点石子
    dp = [INF] * bridge
    dp[0] = 0
    for i in range(1, bridge):
        if i < min_jump:                                  # 还没有合法起跳点
            continue
        dp[i] = min(dp[max(0, i - max_jump):i - min_jump + 1]) + (i in has_stone)

    # 落在 [L-T, L-1] 内任意一点都能一步跳过终点，取其中最小代价
    print(min(dp[max(0, bridge - max_jump):bridge]))


if __name__ == "__main__":
    solve()
