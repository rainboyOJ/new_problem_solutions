#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:35
# update_at: 2026-10-08 03:35

import sys

MOD = 10 ** 9 + 7

type Vec = list[int]      # 一个长度为 d 的模 MOD 向量
type Mat = list[Vec]      # d x d 的模 MOD 矩阵（行优先）


def mat_mul(x: Mat, y: Mat) -> Mat:
    """矩阵乘法：恒等式 z[i][j] = sum_k x[i][k]*y[k][j] mod MOD，内层用 zip 转置求和。"""
    yt = list(zip(*y))                              # 转置后每列变成一行，便于与 x 的行做点积
    return [[sum(a * b for a, b in zip(row, col)) % MOD for col in yt] for row in x]


def mat_pow_elem(base: Mat, e: int) -> int:
    """伴随矩阵快速幂，返回 (base^e)[0][0] —— 即递推第 e 项 h(e)。"""
    d = len(base)                                   # 阶数由矩阵边长给出，无需另传参
    r = [[1 if i == j else 0 for j in range(d)] for i in range(d)]  # 单位矩阵
    while e:
        if e & 1:
            r = mat_mul(r, base)
        base = mat_mul(base, base)
        e >>= 1
    return r[0][0]


def catalan_times_two(d: int) -> Vec:
    """coef[j] = 2 * Catalan(j) = 长为 2(j+1) 的远足方案数，j 取 0..d-1。"""
    fact = [1] * (2 * d + 1)                        # 阶乘表，(2d)! 以内够用
    for i in range(1, 2 * d + 1):
        fact[i] = fact[i - 1] * i % MOD
    inv_fact = [1] * (2 * d + 1)
    inv_fact[2 * d] = pow(fact[2 * d], MOD - 2, MOD)
    for i in range(2 * d, 0, -1):
        inv_fact[i - 1] = inv_fact[i] * i % MOD
    return [2 * fact[2 * j] * inv_fact[j] % MOD * inv_fact[j + 1] % MOD for j in range(d)]


def companion_matrix(d: int) -> Mat:
    """h(t) = sum_j c_j h(t-j) 的伴随矩阵：第一行放系数，次对角线为 1。"""
    a: Mat = [[0] * d for _ in range(d)]
    a[0] = catalan_times_two(d)
    for i in range(1, d):
        a[i][i - 1] = 1                             # 把 f(t-1..t-d+1) 右移一格
    return a


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)                   # 题面的 n、m，均为偶数
    d = m // 2                                      # 递推阶数 d = m/2

    # 初始状态 [h(0), h(-1), ...] = [1, 0, ...]，所以 (A^t)[0][0] 就是 h(t)
    matrix = companion_matrix(d)
    print(mat_pow_elem(matrix, n // 2))


if __name__ == "__main__":
    solve()
