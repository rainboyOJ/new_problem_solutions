#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:22
# update_at: 2026-10-01 05:22

import sys

PARTS = 3                   # 原料种数：大麦、燕麦、小麦
LIMIT = 100                 # 每种饲料份数的上限（题面：份数都小于 100）
MOST = PARTS * (LIMIT - 1)  # 三种饲料份数之和的上限 99+99+99，用来封顶枚举
ZERO = (0, 0, 0)            # 零配比，用于目标配比全为 0 的退化情形
NONE = 0                    # "混合结果不是目标配比的整数倍"的统一哨兵


def portions(mix: tuple[int, ...], target: tuple[int, ...], axis: int | None) -> int:
    """混合结果 mix 相当于几份目标饲料：是整数倍 k ≥ 1 时返回 k，否则返回 NONE。

    axis 是目标配比里第一个非零原料的下标，也是唯一可以拿来定倍数的位置：
    先用它整除出候选 k，再回代校验另外两味原料的比例是否一致。
    """
    if axis is None:  # 目标配比全为 0：只有零混合才是它的（1）倍
        return 1 if mix == ZERO else NONE
    k = mix[axis] // target[axis]
    same_ratio = mix == tuple(k * x for x in target)
    return k if k > 0 and same_ratio else NONE


def blend(target: tuple[int, ...], feeds: list[tuple[int, ...]]) -> tuple[int, ...] | None:
    """按份数总和递增枚举三种饲料的份数，返回第一组能配出目标配比的 (a, b, c, k)。

    总和 s 从 0 递增，同一 s 内按 a 递增、再按 b 递增检查，所以第一组命中的方案
    天然同时满足「总和最小、a 最小、b 最小、c 最小」，也就是题目要求的用量最少；
    无需记录候选最优解，也不可能在中途被更小的总和截胡。
    """
    axis = next((j for j in range(PARTS) if target[j]), None)
    first, second, third = feeds
    for total in range(MOST + 1):
        for a in range(min(total, LIMIT - 1) + 1):
            b_low = max(0, total - a - (LIMIT - 1))  # b 太小会让 c 超过份数上限
            b_high = min(total - a, LIMIT - 1)
            for b in range(b_low, b_high + 1):
                c = total - a - b
                mix = tuple(a * first[j] + b * second[j] + c * third[j] for j in range(PARTS))
                k = portions(mix, target, axis)
                if k:
                    return (a, b, c, k)
    return None  # 枚举完所有份数组合仍无解，对应题面的 NONE


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    target = tuple(next(data) for _ in range(PARTS))                              # 第 1 行：目标饲料
    feeds = [tuple(next(data) for _ in range(PARTS)) for _ in range(PARTS)]       # 第 2..4 行：三种饲料

    ans = blend(target, feeds)
    print("NONE" if ans is None else " ".join(map(str, ans)))


if __name__ == "__main__":
    solve()
