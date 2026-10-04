#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:03
# update_at: 2026-09-30 03:13

import sys
from bisect import bisect_left

NEG = -10**9  # 美学值总和最小也只有 -50*100，用它表示“这些花束装不下”


def prefix_levels(v: int, a: list[list[int]]) -> list[list[int]]:
    """levels[i][t]：花束 1..i 依次放进编号不超过 t 的花瓶时的最大美学值。

    只存前缀最大值即可：第 i 束花定在花瓶 t 时，前 i-1 束花只要全部挤在 t 左侧，
    具体占哪几个花瓶不影响后面的选择，于是“最后一束花放在哪”这一维被压掉了。
    """
    levels = [[0] * (v + 1)]  # 第 0 层：没有花束，任何花瓶前缀的美学值都是 0
    for i, row in enumerate(a, 1):
        prev, cur = levels[-1], [NEG] * (v + 1)
        for t in range(i, v + 1):  # 不足 i 个花瓶放不下 i 束花，保持 NEG
            cur[t] = max(cur[t - 1], prev[t - 1] + row[t - 1])  # 花瓶 t 空着 / 插第 i 束花
        levels.append(cur)
    return levels


def used_vases(f: int, v: int, levels: list[list[int]]) -> list[int]:
    """从右往左回溯：每束花都取“最靠左、又能拼出该层最优值”的花瓶。"""
    pick, target, limit = [0] * f, levels[f][v], v + 1
    for i in range(f, 0, -1):
        pos = bisect_left(levels[i], target, i, limit)  # 该层前缀值第一次达到 target 的花瓶
        pick[i - 1] = pos
        if i > 1:
            # 第 i 束花占了 pos，前 i-1 束花的目标值就是它们在前 pos-1 个花瓶里的最优值
            target, limit = levels[i - 1][pos - 1], pos
    return pick


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    f, v = next(data), next(data)
    a = [[next(data) for _ in range(v)] for _ in range(f)]  # a[i][j]：花束 i+1 放花瓶 j+1 的美学值

    levels = prefix_levels(v, a)
    print(levels[f][v])
    print(*used_vases(f, v, levels))


if __name__ == "__main__":
    solve()
