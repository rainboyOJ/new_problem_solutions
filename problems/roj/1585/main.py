#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:16
# update_at: 2026-09-30 20:16

import sys
from functools import cache


@cache
def comb(n: int, k: int) -> int:
    """C(n, k)，越界取 0：数位 DP 展开成组合数时的查表。"""
    if k < 0 or k > n:
        return 0
    if n == 0 or k == 0:
        return 1
    return comb(n - 1, k - 1) + comb(n - 1, k)


def to_base(n: int, b: int) -> list[int]:
    """n 的 b 进制数字，高位在前；n = 0 时返回 [0]。"""
    digits: list[int] = []
    while n:
        digits.append(n % b)
        n //= b
    return digits[::-1] or [0]


def count(n: int, k: int, b: int) -> int:
    """[0, n] 中 b 进制表示只含 0/1 且恰有 k 个 1 的数的个数。

    从高位到低位卡上界：当前位数字 > 1 时，本位放 0/1 都严格小于 n，
    低位可任选 0/1，直接用组合数收尾；当前位是 1 时，放 0 同样低于上界
    （组合数入账），放 1 继续卡；当前位是 0 时只有放 0 才不越界。
    """
    digits = to_base(n, b)
    ans = 0
    ones = 0  # 已确定的高位里 1 的个数
    for i, d in enumerate(digits):
        rest = len(digits) - i - 1  # 当前位之后还剩多少个低位
        if d > 1:
            # 本位放 0 或 1 都小于 n：从「本位 + 低位」共 rest+1 位里再挑 k-ones 个 1
            return ans + comb(rest + 1, k - ones)
        if d == 1:
            ans += comb(rest, k - ones)  # 本位放 0，rest 个低位自由选 0/1
            ones += 1                    # 本位放 1，继续卡上界
        # d == 0：放 1 会超过 n，只能放 0 继续卡
    return ans + (ones == k)  # n 本身每一位都是 0/1，看它是否恰好 k 个 1


def solve() -> None:
    x, y, k, b = map(int, sys.stdin.buffer.read().split())
    print(count(y, k, b) - count(x - 1, k, b))


if __name__ == "__main__":
    solve()
