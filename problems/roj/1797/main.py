#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:47
# update_at: 2026-10-08 03:47

import sys

MOD = 1000000007  # 题目要求的模数

# 类型别名：2x2 矩阵按行压成四元组 (a00, a01, a10, a11)，省掉嵌套容器的下标噪声
type Mat = tuple[int, int, int, int]


def mul(x: Mat, y: Mat) -> Mat:
    """两个 2x2 矩阵的乘积（模 MOD）。"""
    a, b, c, d = x
    e, f, g, h = y
    return ((a * e + b * g) % MOD, (a * f + b * h) % MOD,
            (c * e + d * g) % MOD, (c * f + d * h) % MOD)


def mpow(base: Mat, e: int) -> Mat:
    """矩阵 base 的 e 次幂（模 MOD），e 可达 1e9。"""
    res: Mat = (1, 0, 0, 1)  # 单位矩阵
    while e:
        if e & 1:
            res = mul(res, base)
        base = mul(base, base)
        e >>= 1
    return res


def kdim_sum(n: int, k: int) -> int:
    """一组询问的答案：n^k 个元素之和 = (Σ_{j=0}^{n-1} M^j)^k 的左上角元素。"""
    fn1, fn = mpow((1, 1, 1, 0), n)[:2]  # M^n 的左上/右上 = F(n+1), F(n)
    fn2 = (fn1 + fn) % MOD              # F(n+2) = F(n+1) + F(n)
    # P = Σ_{j=0}^{n-1} M^j = [[F(n+2)-1, F(n+1)-1], [F(n+1)-1, F(n)]]
    # Python 的 % 对负数已返回非负余数，F(·)-1 为负时无需额外处理
    p: Mat = ((fn2 - 1) % MOD, (fn1 - 1) % MOD, (fn1 - 1) % MOD, fn)
    return mpow(p, k)[0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out: list[int] = []
    for _ in range(T):
        n, k = next(data), next(data)
        out.append(kdim_sum(n, k))
    sys.stdout.write('\n'.join(map(str, out)) + '\n')


if __name__ == "__main__":
    solve()
