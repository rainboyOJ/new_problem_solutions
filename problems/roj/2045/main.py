#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:56
# update_at: 2026-10-01 04:56

import sys

# 一个整数当成一个"位集合"：bit v 为 1 表示邮资 v 可达。
# 这就是第 0 层的值——一张邮票都没贴，只有邮资 0 可达。
LAYER0 = 1


def min_impossible(cap: int, values: list[int], limit: int) -> int:
    """返回从 1 开始不能连续贴出的最小邮资；cap 是答案的搜索上界。"""
    # 多贴一张邮票 = 再选一个面值：第 t 层就是第 t-1 层整体左移 s 位后按位或（每个面值 s）。
    # 层内只做常数次大整数运算，因此只保留一层整数，不需要 O(K) 层的数组。
    mask = (1 << (cap + 1)) - 1  # 只保留邮资 0..cap，位宽不随层数增长
    reachable = LAYER0
    for _ in range(limit):
        nxt = reachable
        for s in values:
            nxt |= (reachable << s) & mask
        if nxt == reachable:  # 再贴也贴不出新邮资，更多张数同样贴不出
            break
        reachable = nxt

    # 邮资 v（v >= 1）可达 <=> reachable 的第 v 位为 1，等价于第 v-1 位为 0 的 gaps 里那一位置 1。
    gaps = ~(reachable >> 1)
    lowest_gap = gaps & -gaps  # 最低的 1 位，就是第一个不可达邮资
    return lowest_gap.bit_length() - 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    stamps, kinds = next(data), next(data)  # 可用邮票张数上限 K，面值种数 N
    values = sorted({next(data) for _ in range(kinds)})  # 重复面值不影响可达性，先去重

    # 答案不会超过 K * 最大面值：K*max+1 至少要 K+1 张邮票，本来就不可能贴出；
    # 而一旦出现空隙，它必是最小的不可达值——比它大的邮资都能用减法回到它之前，
    # 所以更早处就已经断了。于是搜索上界取 K*max 即可。
    cap = stamps * values[-1]
    print(min_impossible(cap, values, stamps))


if __name__ == "__main__":
    solve()
