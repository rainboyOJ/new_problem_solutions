#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:42
# update_at: 2026-09-30 07:48

import sys


def bait_catch(rate: list[int], drop: list[int]) -> list[int]:
    """一个鱼塘从下钩到收竿、每一分钟能钓到的鱼数，按递减顺序列出。

    每分钟的收益比上一分钟少 drop，减到非正数就没鱼可钓，所以钓满
    ceil(rate/drop) 分钟即可，得到 rate, rate-drop, ..., rate-(count-1)*drop。
    """
    count = -(-rate // drop)  # ceil(rate/drop)，即这个鱼塘值得钓的分钟数
    return [rate - k * drop for k in range(count)]


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    rate = data[1:n + 1]              # 各鱼塘第 1 分钟能钓到的鱼数
    drop = data[n + 1:2 * n + 1]      # 各鱼塘每钓一分钟的收益衰减量
    walk = data[2 * n + 1:3 * n]      # 第 i 个到第 i+1 个鱼塘的路程时间
    deadline = data[3 * n]            # 截止时间 T

    best = 0
    spent = 0                         # 走到第 last 个鱼塘累计花掉的路程时间
    picks: list[int] = []             # 1..last 号鱼塘全部可用分钟的收益，降序
    for last in range(1, n + 1):
        left = deadline - spent       # 总时间减去路程，其余都能用来钓鱼
        if left < 0:                  # 时间已经耗光，更远的鱼塘只会更亏
            break
        picks += bait_catch(rate[last - 1], drop[last - 1])
        picks.sort(reverse=True)
        best = max(best, sum(picks[:left]))  # 挑收益最高的 left 分钟去钓
        if last < n:
            spent += walk[last - 1]
    print(best)


if __name__ == "__main__":
    solve()
