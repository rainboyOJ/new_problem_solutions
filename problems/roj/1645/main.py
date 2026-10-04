#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-03-31 09:00
# update_at: 2026-03-31 09:00

import sys

MOD = 10000  # 题目要求的模数
Matrix2x2 = tuple[int, int, int, int]  # 行优先展平表示 2x2 矩阵 (m00, m01, m10, m11)
TRANS: Matrix2x2 = (1, 1, 1, 0)        # 斐波那契状态转移矩阵 [[1, 1], [1, 0]]
I2: Matrix2x2 = (1, 0, 0, 1)           # 2x2 单位矩阵


def mat_mul(a: Matrix2x2, b: Matrix2x2) -> Matrix2x2:
    """计算两个 2x2 矩阵的乘积模 10000。"""
    return (
        (a[0] * b[0] + a[1] * b[2]) % MOD,
        (a[0] * b[1] + a[1] * b[3]) % MOD,
        (a[2] * b[0] + a[3] * b[2]) % MOD,
        (a[2] * b[1] + a[3] * b[3]) % MOD,
    )


def mat_pow(base: Matrix2x2, exp: int) -> Matrix2x2:
    """计算 2x2 矩阵的 exp 次幂模 10000。"""
    res = I2
    while exp:
        if exp & 1:
            res = mat_mul(res, base)
        base = mat_mul(base, base)
        exp >>= 1
    return res


def fib(n: int) -> int:
    """计算第 n 项斐波那契数模 10000。"""
    if n == 0:
        return 0
    # [[F_{n+1}, F_n], [F_n, F_{n-1}]] = [[1, 1], [1, 0]]^n
    # 所以 TRANS^n 的右上方元素（下标 1）即为 F_n
    return mat_pow(TRANS, n)[1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for n in data:
        if n == -1:
            break
        out.append(str(fib(n)))
    print("\n".join(out))


if __name__ == "__main__":
    solve()
