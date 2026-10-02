#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 18:00
# update_at: 2026-10-02 18:00

import sys
from decimal import Decimal, getcontext

PRECISION = 40  # 有效数字 40 位，远超题目 1e-6 的相对误差要求


def solve() -> None:
    getcontext().prec = PRECISION
    it = iter(sys.stdin.read().split())
    n, m = int(next(it)), int(next(it))
    p_text = next(it)
    whole, _, frac = p_text.partition('.')  # 有限小数按位数缩放成整数，全程只用整数运算
    scale = 10 ** len(frac)                 # 缩放系数：小数 6 位时 scale = 10^6
    p_scaled = int(whole or "0") * scale + int(frac or "0")

    # Alice 的宝石数在 [0, n+m] 上随机游走：正面 -1（0 处 Bob 空手，状态不动），
    # 反面 +1（n+m 处 Alice 空手，状态不动），两个端点等价于反射壁。
    # 游戏在 Alice 的宝石数"回到出发值 n"的那个回合结束，由回返定理 E = 1/π(n)，
    # 其中 π(k) ∝ (p/q)^k，于是 E = Σ_{k=0}^{n+m} ((1-p)/p)^{k-n}。
    # 整数化：令 a/b = (scale-p_scaled)/p_scaled，通分 a^n·b^m 后
    # 分子分母都是至多 1200 位的整数，避免浮点误差也避免大分数归约。
    a = scale - p_scaled  # q = 1-p 的缩放分子
    b = p_scaled          # p 的缩放分子
    total = n + m
    num = sum(a ** k * b ** (total - k) for k in range(total + 1))  # Σ a^k·b^{n+m-k}
    den = a ** n * b ** m
    print(f"{Decimal(num) / Decimal(den):.10f}")


if __name__ == "__main__":
    solve()
