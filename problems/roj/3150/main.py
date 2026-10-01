#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:20
# update_at: 2026-10-01 21:20

import sys

NEG = -10**30  # 不可达状态；体力可以全为 0，所以不能用 -1 这类普通哨兵


def best_gain(u: list[int], b: int, wrapping: bool) -> int:
    """断环成链后睡满 b 小时的最大恢复体力。

    awake[j] / asleep[j]：扫到当前小时、共睡了 j 小时，且当前小时清醒 / 睡着的最大体力。
    入睡的第一个小时不恢复体力，所以只有前一小时也睡着时本小时才累加 U_i。

    wrapping = False：第 1 小时清醒、或是它所在睡觉段的第一个小时（不计 U_1）；
    wrapping = True：第 1 小时在续上一轮第 N 小时的觉，它必定睡着且计入 U_1，
    代价是第 N 小时也必须睡着，否则「续睡」不成立。
    """
    awake = [NEG] * (b + 1)
    asleep = [NEG] * (b + 1)
    if wrapping:
        asleep[1] = u[0]                    # 第 1 小时已睡熟，计入 U_1
    else:
        awake[0], asleep[1] = 0, 0          # 第 1 小时清醒，或刚入睡不计 U_1
    for gain in u[1:]:
        # NEG 远小于任何合法值，不可达项加上 gain 仍不可能被 max 选中，无需额外保护
        ripe = [v + gain for v in asleep[:b]]             # 前一小时也睡着 → 睡熟了
        new_awake = list(map(max, awake, asleep))         # 本小时清醒，体力不变
        asleep = [NEG] + list(map(max, awake[:b], ripe))  # 本小时刚入睡，不计 gain
        awake = new_awake
    return asleep[b] if wrapping else max(awake[b], asleep[b])


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, b = next(data), next(data)
    u = [next(data) for _ in range(n)]
    # 两类互补：第 1 小时要么是所在段的第一个小时（不续睡），要么在续上一轮第 N 小时的觉。
    # 续睡那一类精确覆盖了所有跨环方案；不续睡那一类只会少算 U_1，绝不虚高，
    # 所以取 max 就是答案，不需要枚举断环位置。
    print(max(best_gain(u, b, False), best_gain(u, b, True)))


if __name__ == "__main__":
    solve()
