#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 17:40
# update_at: 2026-10-02 17:40

import sys
from math import gcd

MAX_A = 10**6  # 题面数据范围里 a_i 的上限


def build_omega() -> list[int]:
    """omega[n] = n 的质因数个数（计重数）：质数幂 p^k 给它的每个倍数贡献 1。"""
    omega = [0] * (MAX_A + 1)
    for p in range(2, MAX_A + 1):
        if omega[p]:  # 下标是合数时已被更小的质数标记过
            continue
        power = p
        while power <= MAX_A:
            for multiple in range(power, MAX_A + 1, power):
                omega[multiple] += 1  # 多整除一个 p，就多计一个质因数
            power *= p
    return omega


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 序列长度
    omega = build_omega()

    # 扫输入时同步维护 ΣΩ(a_i) 与全体 a_i 的 gcd，不存整个序列
    total = 0
    common = 0
    for _ in range(n):
        value = next(data)  # 第 i 个元素 a_i
        total += omega[value]
        common = gcd(common, value)

    # 每个 a_i / g 的一个质因子恰好要占一次操作
    print(total - n * omega[common])


if __name__ == "__main__":
    solve()
