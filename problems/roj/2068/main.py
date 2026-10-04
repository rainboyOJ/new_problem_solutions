#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 06:19
# update_at: 2026-10-01 06:42

import sys
from itertools import combinations
from math import lcm

# 传动比 a/b 记为整数 a * W[b]（W[b] = L//b，L 是 5..40 的公倍数），
# 这样比值、相邻差、方差全在整数域精确计算，不存在浮点误差。
L = lcm(*range(5, 41))
W = [0] * 5 + [L // b for b in range(5, 41)]  # W[b] = L//b，下标 5..40 有效


def rank_score(nums: list[int], m: int) -> int:
    """由 m+1 个传动比整数（m 个相邻差）算“比较用方差分数”：m*Σ(相邻差)² - (首尾差)²。

    真实方差 = (m·Σd² - (Σd)²) / (L²·m²)，L、m 对每个方案相同，
    所以只需比较这个整数：越小方差越小。
    """
    nums.sort()
    first, last = nums[0], nums[-1]
    span = last - first            # Σd = 最大比 - 最小比（望远镜求和）
    sq = sum((b - a) ** 2 for a, b in zip(nums, nums[1:]))  # Σ d²
    return m * sq - span * span


def best_combo(f1: int, f2: int, r1: int, r2: int, F: int, R: int) -> tuple[tuple[int, ...], tuple[int, ...]]:
    """在所有合法方案里找方差分数最小的 (前齿轮, 后齿轮)；分数相同取字典序最小者在前。"""
    m = F * R - 1              # 相邻差的个数

    best_score: int | None = None  # 当前最小方差分数
    best: tuple[tuple[int, ...], tuple[int, ...]] | None = None

    for front in combinations(range(f1, f2 + 1), F):  # 字典序枚举前齿轮组合
        f_min, f_max = front[0], front[-1]
        # scaled[b] = 这个前齿轮组合配后齿轮 b 时的 F 个传动比整数（内部升序）
        scaled = [[a * W[b] for a in front] for b in range(r1, r2 + 1)]

        if R == 2:
            # 只需后齿轮较小者 x 与较大者 y：
            # 3 倍约束 f_max/y  >= 3*f_min/x  ⇔  y*f_max >= 3*x*f_min，
            # 直接算出每个 x 的合法 y 下界，跳过全部不合法对。
            for x in range(r1, r2):
                lo = (3 * f_min * x + f_max - 1) // f_max  # y 的最小合法值（向上取整）
                if lo < x + 1:
                    lo = x + 1
                for y in range(lo, r2 + 1):
                    score = rank_score(scaled[x - r1] + scaled[y - r1], m)
                    # 只替换严格更小者：枚举顺序即字典序，天然满足并列时取最小组合
                    if best_score is None or score < best_score:
                        best_score, best = score, (front, (x, y))
        else:
            for rear in combinations(range(r1, r2 + 1), R):
                if f_max * rear[-1] < 3 * f_min * rear[0]:  # 最大比不足最小比 3 倍
                    continue
                nums = [v for b in rear for v in scaled[b - r1]]
                score = rank_score(nums, m)
                if best_score is None or score < best_score:
                    best_score, best = score, (front, rear)

    return best  # 题面保证至少一组合法解


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    F, R = next(data), next(data)
    f1, f2, r1, r2 = next(data), next(data), next(data), next(data)

    best = best_combo(f1, f2, r1, r2, F, R)
    print(' '.join(map(str, best[0])))
    print(' '.join(map(str, best[1])))


if __name__ == "__main__":
    solve()
