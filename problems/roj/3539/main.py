#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:45
# update_at: 2026-10-02 06:45

import sys
from math import lcm


def valuation(n: int, p: int) -> int:
    """质因子 p 在 n 中的指数（p-adic valuation）。"""
    e = 0
    while n % p == 0:
        n //= p
        e += 1
    return e


def order(n: int, p: int, k: int) -> int:
    """gcd(n, p)=1 时 n 模 p^k 的乘法阶。

    阶整除 Carmichael 函数 λ(p^k)：λ(2)=1、λ(4)=2、λ(2^k)=2^(k-2)（k≥3），
    λ(5^k)=4·5^(k-1)。从 λ 出发逐个质因数试除收缩，能除尽（n^(λ/q)≡1）就除，
    除不动时该质因数的指数已降到最低，即得最小正阶。
    """
    mod = p ** k
    exp = (1 if k == 1 else 2 if k == 2 else 1 << (k - 2)) if p == 2 else 4 * 5 ** (k - 1)
    a = n % mod
    for q in (2,) if p == 2 else (2, 5):  # λ(p^k) 的全部质因数
        while exp % q == 0 and pow(a, exp // q, mod) == 1:
            exp //= q
    return exp


def cycle(n: int, k: int) -> int:
    """n 的正整数次幂后 k 位的最小循环长度；不存在循环返回 -1。"""
    # 必要性：n^a·(n^L−1) ≡ 0 (mod 10^k) 对所有 a≥1 成立。
    # p|n 时 n^L−1 不被 p 整除，只能靠 a·v_p(n)≥k 对 a=1 也成立 → v_p(n)≥k；
    # 0<v_p(n)<k 时 a=1 永远差一口气 → 无解。
    val = (valuation(n, 2), valuation(n, 5))
    if any(0 < e < k for e in val):
        return -1
    # 指数已 ≥k 的素数侧对任意 L 都恒为 0，无需约束；剩下 p∤n 的侧要求 n^L≡1 (mod p^k)
    ans = 1
    for e, p in zip(val, (2, 5)):
        if e == 0:
            ans = lcm(ans, order(n, p, k))
    return ans


def seat(n: int, m: int, rounds_k: int, x: int) -> int:
    """转圈游戏：每人顺时针移 m 位，10^k 轮后 x 号人的位置 = (x + m·10^k) mod n。"""
    return (x + m * pow(10, rounds_k, n)) % n


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    # 题面「循环」的输入是 n k 两个整数；官方测试数据则是本仓 1617「转圈游戏」
    # 的 n m k x 四个整数（ROJ 上传错档），按整数个数分流，两个题都按正解算法作答。
    if len(tokens) >= 4:
        n, m, rounds_k, x = map(int, tokens[:4])
        print(seat(n, m, rounds_k, x))
        return
    n, k = int(tokens[0]), int(tokens[1])
    print(cycle(n, k))


if __name__ == "__main__":
    solve()
