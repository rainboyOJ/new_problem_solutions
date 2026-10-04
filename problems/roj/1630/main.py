#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:10
# update_at: 2026-09-30 23:10

import sys

sys.set_int_max_str_digits(0)   # 解除 $10^{10000}$ 级大数与字符串互转的默认 4300 位上限


def trailing_zeros(x: int) -> int:
    """取 x 二进制尾部 0 的个数，即 x 含因子 2 的幂次。"""
    return (x & -x).bit_length() - 1


def binary_gcd(a: int, b: int) -> int:
    """Stein 二进制 GCD：只用移位、减法和比较，避免对 $10^{10000}$ 级大数做除法取模。"""
    if a == 0:                      # 较小数为 0 时 gcd 就是另一个数
        return b
    if b == 0:
        return a

    shift = min(trailing_zeros(a), trailing_zeros(b))  # 公共因子 2 的个数

    a >>= trailing_zeros(a)         # 之后 a 一直是奇数
    while b:
        b >>= trailing_zeros(b)     # 去掉 b 的尾零：奇偶差异不贡献 gcd
        if a > b:
            a, b = b, a
        b -= a                      # 奇 - 奇 = 偶，下一轮还能整除 2，规模减半
    return a << shift               # 补回公共因子 2


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())  # 仅按位置顺序消费两个大整数字串
    a = int(next(data))                           # 第一个 $10^{10000}$ 级大数
    b = int(next(data))
    print(binary_gcd(a, b))


if __name__ == "__main__":
    solve()
