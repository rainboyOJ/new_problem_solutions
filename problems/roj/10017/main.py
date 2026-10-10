#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-10 08:04
# update_at: 2026-10-10 08:42

import sys

MOD = 1_000_000_007
type FactList = list[int]  # 组合数预处理数组，下标 i 存 i! 或其逆元


def build_combinations(n: int) -> tuple[FactList, FactList]:
    """预处理阶乘与阶乘逆元，用来 O(1) 求组合数。"""
    fact = [1] * (n + 1)
    inv_fact = [1] * (n + 1)
    for i in range(1, n + 1):
        fact[i] = fact[i - 1] * i % MOD
    inv_fact[n] = pow(fact[n], MOD - 2, MOD)
    for i in range(n - 1, -1, -1):
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD
    return fact, inv_fact


def coefficient(n: int, pos: int, fact: FactList, inv_fact: FactList) -> int:
    """第 pos 个数（从 1 开始）在最终答案中的系数：C(⌈n/2⌉-1, ⌈pos/2⌉-1) 带 (−1)^(⌈pos/2⌉-1)。"""
    if n % 2 == 1 and pos % 2 == 0:
        return 0  # n 为奇数时 (1−x²)^k 只有偶次项，奇数下标全为 0
    half_pos = (pos + 1) // 2
    half_n = (n + 1) // 2
    choose = fact[half_n - 1] * inv_fact[half_pos - 1] % MOD * inv_fact[half_n - half_pos] % MOD
    return -choose if half_pos % 2 == 0 else choose


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return

    fact, inv_fact = build_combinations(n)
    values = [next(data) for _ in range(n)]
    answer = sum(value * coefficient(n, pos, fact, inv_fact)
                 for pos, value in enumerate(values, 1)) % MOD
    print(answer)


if __name__ == "__main__":
    solve()
