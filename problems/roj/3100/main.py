#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:03
# update_at: 2026-10-01 17:10

import sys


def merge(v: int, m: int, a: int, b: int) -> tuple[int, int]:
    """并入条件 x ≡ b (mod a)：由 x = v + m*t 解出 t，返回新剩余类的 (余数, 模数)。"""
    t = (b - v) * pow(m, -1, a) % a  # 解 m*t ≡ b-v (mod a)；a_i 两两互质，故 m 可逆
    return (v + m * t) % (m * a), m * a


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    v, m = 0, 1  # 空约束：x ≡ 0 (mod 1) 对一切 x 成立，是合并的单位元
    for _ in range(n):
        a, b = next(data), next(data)  # 建 a 个棚剩 b 头牛，即 x ≡ b (mod a)
        v, m = merge(v, m, a, b)

    print(v or m)  # v 是 [0, m) 内的解，题目要正整数：v = 0 时取周期 m


if __name__ == "__main__":
    solve()
