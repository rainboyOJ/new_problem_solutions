#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:50
# update_at: 2026-10-08 03:50

import sys

type Matrix = tuple[int, int, int, int]  # 2x2 矩阵按行主序压平：[[a,b],[c,d]] -> (a,b,c,d)


def mat_mul(A: Matrix, B: Matrix, p: int) -> Matrix:
    """2x2 矩阵乘法（模 p）：展开成 8 次标量乘法，不做循环。"""
    return (
        (A[0] * B[0] + A[1] * B[2]) % p, (A[0] * B[1] + A[1] * B[3]) % p,
        (A[2] * B[0] + A[3] * B[2]) % p, (A[2] * B[1] + A[3] * B[3]) % p,
    )


def mat_pow(M: Matrix, e: int, p: int) -> Matrix:
    """矩阵快速幂 M^e：n 可达 1e18，二进制拆分后只需 O(log e) 次乘法。"""
    R: Matrix = (1, 0, 0, 1)  # 单位矩阵，e = 0（即 n = 0）时答案直接由它还原成 f(0)
    while e:
        if e & 1:
            R = mat_mul(R, M, p)
        M = mat_mul(M, M, p)
        e >>= 1
    return R


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data)
    out: list[str] = []
    for _ in range(t):
        f0, a, b, c, d, n, p = (next(data), next(data), next(data),
                                next(data), next(data), next(data), next(data))
        # 系数可能为负（题面 0<=|x|<p），Python 的 % 结果恒非负，直接取模即可
        f0 %= p; a %= p; b %= p; c %= p; d %= p
        # 齐次坐标：把 f(i) 写成 x_i / y_i，则 (x_i,y_i) = [[a,b],[c,d]]^i (f0,1)
        R = mat_pow((a, b, c, d), n, p)
        x = (R[0] * f0 + R[1]) % p
        y = (R[2] * f0 + R[3]) % p
        out.append(str(x * pow(y, -1, p) % p))  # pow(y,-1,p) 只要求 gcd(y,p)=1，不要求 p 是素数
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
