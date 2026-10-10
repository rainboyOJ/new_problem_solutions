#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:20
# update_at: 2026-10-08 02:20

import sys

# 行列都从 0 编号后，(i, j) 是白格当且仅当 i & j == 0。
# 把每个白格 (i, j) 的父亲定为“低位 1 更靠下的那一维的下标减 1”得到的白邻居
# （lsb(i) < lsb(j) 时父亲是 (i-1, j)，反之是 (i, j-1)，(0, 0) 是全局树根），
# 于是白格图是一棵树；矩形内的连通块数 = 矩形内“父亲落在矩形外”的白格数。


def count_no_bit(X: int, M: int) -> int:
    """数出满足 0 <= j <= X 且 j & M == 0 的 j 的个数。"""
    if X < 0:
        return 0
    res = 0
    # 从高位往低位贴着 X 的前缀走路：X 该位为 1 时让 j 该位取 0，低位在 M 为 0 的位上任取
    for b in range((X | M).bit_length() - 1, -1, -1):
        if X >> b & 1:
            free = b - (M & ((1 << b) - 1)).bit_count()   # 本位以下 M 为 0、也就是 j 可以任取的位数
            res += 1 << free
            if M >> b & 1:
                return res          # 该位 M 也为 1，j 无法继续与 X 的前缀相同
    return res + (1 if X & M == 0 else 0)   # 补上 j == X 本身


def bound_mask(v: int) -> int:
    """上界 v 对应的掩码 v | (2^lsb(v) - 1)：j 与它按位与为 0 等价于 j & v == 0 且 lsb(j) > lsb(v)。"""
    return v | ((1 << (v & -v).bit_length() - 1) - 1)


def block_count(x1: int, y1: int, x2: int, y2: int) -> int:
    """矩形 [x1, x2] × [y1, y2]（0 编号，闭区间）内的白格连通块数。"""
    ans = 0
    if x1 > 0:
        # 第 x1 行上父亲 (i-1, j) 越过上边界的白格：要求 j & Mx == 0 即 lsb(j) > lsb(x1)
        M = bound_mask(x1)
        ans += count_no_bit(y2, M) - count_no_bit(y1 - 1, M)
    if y1 > 0:
        # 第 y1 列上父亲 (i, j-1) 越过左边界的白格，行列互换同理
        M = bound_mask(y1)
        ans += count_no_bit(x2, M) - count_no_bit(x1 - 1, M)
    return ans + (1 if x1 == 0 and y1 == 0 else 0)   # 全局树根 (0, 0) 本身


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    q = next(data, 0)
    out: list[str] = []
    for _ in range(q):
        x1, y1, x2, y2 = next(data) - 1, next(data) - 1, next(data) - 1, next(data) - 1
        out.append(str(block_count(x1, y1, x2, y2)))
    sys.stdout.write('\n'.join(out) + ('\n' if out else ''))


if __name__ == "__main__":
    solve()
