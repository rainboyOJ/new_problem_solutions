#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:49
# update_at: 2026-10-01 16:49

import sys
from array import array
from itertools import product

SUIT = 13                     # 每种花色 13 张
CARDS = 54                    # 一副牌 54 张，含大小王
DIM = SUIT + 2                # 计数维取 0..14：13 之外多留一位，放"王补进来的那一张"
SLOTS = 25                    # (x, y)：两张王各自被要求变成的花色，0 = 还没翻到，1..4 = 黑桃红桃梅花方块
BLOCK = DIM ** 3 * SLOTS      # 计数维 a 加 1 要跨过的距离
SPAN = DIM ** 4 * SLOTS       # 状态总数
INV = [0.0] + [1.0 / i for i in range(1, CARDS + 1)]      # 隐式概率只在这里出现：1/剩余张数
PAIRS = sorted(((x, y) for x in range(5) for y in range(5)),
               key=lambda p: -((p[0] > 0) + (p[1] > 0)))  # 两张王先落位，保证后继状态已经算好
DEAD = 1e30                   # 余牌翻光也补不齐目标的哨兵，比真值 54 大 26 个数量级


def impossible(A: int, B: int, C: int, D: int) -> bool:
    """目标是否超出牌库：某花色要得比 13 张还多，多出来的部分只有大小王能补。"""
    return sum(max(0, want - SUIT) for want in (A, B, C, D)) > 2


def expected(A: int, B: int, C: int, D: int) -> float:
    """自底向上填期望表，返回 f[0]：一张牌都没翻时，翻到目标的期望张数。"""
    f = array("d", bytes(8 * SPAN))
    for a, b, c, d in product(range(SUIT, -1, -1), repeat=4):
        base = (((a * DIM + b) * DIM + c) * DIM + d) * SLOTS
        for x, y in PAIRS:
            o = base + 5 * x + y
            # 王记在 x / y 上、不顶替计数维，所以"这一门够不够"看 a + [x 是这门] + [y 是这门]
            if (a + (x == 1) + (y == 1) >= A and b + (x == 2) + (y == 2) >= B
                    and c + (x == 3) + (y == 3) >= C and d + (x == 4) + (y == 4) >= D):
                f[o] = 0.0                                  # 目标已达成，停手
                continue
            left = CARDS - a - b - c - d - (x > 0) - (y > 0)  # 没翻开的牌，含还没落位的王
            if left <= 0:
                f[o] = DEAD                                 # 牌翻光了还差，这条路永远到不了目标
                continue
            inv = INV[left]
            v = 1.0 + inv * (
                (SUIT - a) * f[o + BLOCK]                    # 翻出黑桃
                + (SUIT - b) * f[o + BLOCK // DIM]           # 翻出红桃
                + (SUIT - c) * f[o + BLOCK // DIM // DIM]    # 翻出梅花
                + (SUIT - d) * f[o + SLOTS])                 # 翻出方块
            if x == 0:                                       # 翻到第一张王：当场选一门，选期望最小的
                v += inv * min(f[o + 5 * u] for u in (1, 2, 3, 4))
            if y == 0:                                       # 翻到第二张王，同样当场选
                v += inv * min(f[o + u] for u in (1, 2, 3, 4))
            f[o] = v
    return f[0]


def solve() -> None:
    A, B, C, D = map(int, sys.stdin.buffer.read().split())
    print(f"{-1.0 if impossible(A, B, C, D) else expected(A, B, C, D):.3f}")


if __name__ == "__main__":
    solve()
