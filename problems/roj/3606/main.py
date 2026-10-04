#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:18
# update_at: 2026-10-02 10:18

import sys

NEG = -(1 << 62)  # 分数下界的哨兵：|分数| 不可能超过 n·2·10^9


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    p = int(next(data))

    best = NEG        # 全体小朋友分数的最大值（带符号）
    end_here = 0      # 以当前人结尾的最大子段和（Kadane 滚动值）
    trait = NEG       # 特征值：前缀 [1..i] 内的最大子段和
    g = NEG           # 已看过的人中 score_j + trait_j 的最大值

    for i in range(n):
        a = int(next(data))
        end_here = max(end_here + a, a)
        trait = max(trait, end_here)  # 特征值不要求子段以 i 结尾

        # 分数：第 1 个人是自己的特征值；
        # 其他人是前面所有人中「分数 + 特征值」的最大值
        score = trait if i == 0 else g
        best = max(best, score)
        g = max(g, score + trait)

    # 输出保持符号：负数输出 -(|best| mod p)，非负输出 best mod p
    print(best % p if best >= 0 else -(abs(best) % p))


if __name__ == "__main__":
    solve()
