#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:20
# update_at: 2026-09-30 23:20

import sys


def merge(v: int, m: int, a: int, b: int) -> tuple[int, int]:
    """并入条件 x ≡ b (mod a)，返回合并后的 (余数, 模数)。

    已解部分等价于 x = v + m*t；代入得 m*t ≡ b - v (mod a)。题面保证 a 两两互质，
    而 m 是此前若干 a 的乘积，故 gcd(m, a) = 1，逆元存在，t 在模 a 下唯一。
    """
    t = (b - v) * pow(m, -1, a) % a  # `% a` 把负差值也归一化到 [0, a)，新余数最小非负
    return v + m * t, m * a          # 新模数 m*a 就是这组条件的公共周期


def crt(congs: list[tuple[int, int]]) -> int:
    """按输入顺序合并同余条件 x ≡ b_i (mod a_i)，返回最小正解。"""
    v, m = 0, 1  # x = 0 + 1*t 对一切 x 成立，是合并的单位元
    for a, b in congs:
        v, m = merge(v, m, a, b)
    return v or m  # v = 0 表示解是周期的整数倍，最少养猪数取 m 本身


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    congs = [(next(data), next(data)) for _ in range(n)]  # 每行一组 (猪圈数, 剩余猪数)
    print(crt(congs))


if __name__ == "__main__":
    solve()
