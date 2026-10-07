#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:27
# update_at: 2026-10-08 04:27

import sys

# 每个元素是一族同余式（最小正解, 模数, 容斥符号）；V 被"喜欢"当且仅当它落在其中任意一族。
# 由 D(x) = k <=> x ≡ k (mod 9) 推出 V = 9k*m + k^2，九族按 V mod 9 归并后只剩七个正族，
# 其中 k=2/k=7 与 k=4/k=5 两组有重叠，用两个 -1 项做容斥扣回。
type Term = tuple[int, int, int]  # (最小正解, 模数, 容斥符号)

TERMS: tuple[Term, ...] = (
    (1, 9, 1),      # k=1，也是整个 mod 9 == 1 类
    (4, 18, 1),     # k=2
    (49, 63, 1),    # k=7
    (16, 36, 1),    # k=4
    (25, 45, 1),    # k=5
    (9, 27, 1),     # k=3，也覆盖 k=6
    (81, 81, 1),    # k=9（81 | V，所以最小正解写 81 而不是 0）
    (112, 126, -1), # k=2 与 k=7 的重叠部分
    (160, 180, -1), # k=4 与 k=5 的重叠部分
)


def count_upto(n: int) -> int:
    """[1, n] 中"小D喜欢的数"的个数，即各族等差数列项数之和。"""
    return sum(
        sign * ((n - first) // mod + 1)  # 首项 first、公差 mod 的等差数列项数
        for first, mod, sign in TERMS
        if n >= first                    # n 小于首项时这一族一个都没有
    )


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)  # 数据组数
    out: list[str] = []
    for _ in range(T):
        L, R = next(data), next(data)
        out.append(str(count_upto(R) - count_upto(L - 1)))  # 前缀相减得区间计数
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
