#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:43
# update_at: 2026-09-30 23:43

import sys

# 转移矩阵 T：[f(k+1), f(k)] · T = [f(k+2), f(k+1)]，且 T^k 的左上角就是 f(k+1)
FIB = ((1, 1), (1, 0))


def mat_mul(a: tuple, b: tuple, m: int) -> tuple:
    """2×2 矩阵乘法，边乘边对 m 取模。"""
    return tuple(
        tuple(sum(a[i][k] * b[k][j] for k in range(2)) % m for j in range(2))
        for i in range(2)
    )


def mat_pow(base: tuple, n: int, m: int) -> tuple:
    """矩阵快速幂：返回 base^n mod m，O(log n) 次矩阵乘法。"""
    result = ((1, 0), (0, 1))  # 单位矩阵
    while n:
        if n & 1:
            result = mat_mul(result, base, m)
        base = mat_mul(base, base, m)
        n >>= 1
    return result


def solve() -> None:
    n, m = map(int, sys.stdin.buffer.read().split())

    # 恒等式 S_n = f_1 + ... + f_n = f_{n+2} - 1，
    # 而 T^(n+1) 的左上角是 f_{n+2}，故只需一次矩阵快速幂。
    print((mat_pow(FIB, n + 1, m)[0][0] - 1) % m)


if __name__ == "__main__":
    solve()
