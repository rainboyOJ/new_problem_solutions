#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:21
# update_at: 2026-10-01 00:21

import sys

P = 10**6 + 3  # 模数，质数：小于它的阶乘模它非零，Lucas 分解可用

# 阶乘表：P 以内的 i! mod P，Lucas 每一位的组合数都靠它
fact = [1] * P
for i in range(1, P):
    fact[i] = fact[i - 1] * i % P


def comb(n: int, k: int) -> int:
    """求 C(n, k) mod P：n 可达 2e9 超过 P，按 Lucas 定理按 P 进制逐位组合。"""
    res = 1
    while n or k:
        a, b = n % P, k % P   # 当前 P 进制位
        if b > a:             # 某一位下标超过上标，整项为 0
            return 0
        res = (res * fact[a] * pow(fact[b], P - 2, P) * pow(fact[a - b], P - 2, P)) % P
        n, k = n // P, k // P
    return res


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out: list[str] = []

    for _ in range(T):
        n, l, r = next(data), next(data), next(data)
        m = r - l + 1              # 元素取值个数
        # 按长度枚举求和得 hockey-stick 恒等式：Σ_{i=1..n} C(m+i-1, i) = C(m+n, n)
        # 非空序列至少含一个元素，从"长度 0 的空序列"对应的那 1 项里扣掉
        out.append(str((comb(m + n, n) - 1) % P))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
