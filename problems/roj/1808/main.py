#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 04:32
# update_at: 2026-10-08 04:32

import sys

MOD13 = 10 ** 13      # 题目要求的模数
MOD4 = 10 ** 4        # 基底模数，取它是因为 pi(10^4) 很短且规律标准
PERIOD4 = 15000       # 皮萨诺周期 pi(10^k) = 15 * 10^(k-1)（k >= 3）


def fib_mod(n: int, mod: int) -> int:
    """快速倍增求 F_n mod mod（迭代处理 n 的二进制位，从最高位起）。"""
    fk, fk1 = 0, 1 % mod                       # 当前持有的 (F_k, F_{k+1})
    for bit in bin(n)[2:]:
        c = fk * ((2 * fk1 - fk) % mod) % mod  # F_{2k}   = F_k * (2F_{k+1} - F_k)
        d = (fk * fk + fk1 * fk1) % mod        # F_{2k+1} = F_k^2 + F_{k+1}^2
        fk, fk1 = (d, (c + d) % mod) if bit == '1' else (c, d)
    return fk


def solutions(a: int) -> list[int]:
    """逐层截断提升，返回模 10^13 下一个周期内所有满足 F_n ≡ a 的下标。"""
    cur: list[int] = []
    f0, f1 = 0, 1                              # 底层暴力枚举 pi(10^4) 项
    for n in range(PERIOD4):
        if f0 == a % MOD4:
            cur.append(n)
        f0, f1 = f1, (f0 + f1) % MOD4

    mod, period = MOD4, PERIOD4
    while cur and mod < MOD13:
        step, period, mod = period, period * 10, mod * 10   # pi 每层恰好扩大 10 倍
        target = a % mod                       # 只比较当前层的低位，不能用完整的 a
        nxt: list[int] = []
        for x in cur:
            for c in range(10):                # 新解必落在上一层的 x + c*step 上
                n = x + c * step
                if fib_mod(n, mod) == target:
                    nxt.append(n)
        cur = nxt
    return cur


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a = next(data)
    print(min(solutions(a), default=-1))       # 无解时 default 给出 -1


if __name__ == "__main__":
    solve()
