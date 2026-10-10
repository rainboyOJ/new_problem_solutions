#!/usr/bin/env python3
# 2026-10-10 11:00

import sys

MOD = 10 ** 9 + 7


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    out = []
    for _ in range(t):
        n = int(next(it)); a1 = int(next(it)); a2 = int(next(it))
        x = int(next(it)); y = int(next(it))
        out.append(str(square_sum(n, a1, a2, x, y)))
    sys.stdout.write('\n'.join(out) + '\n')


def square_sum(n: int, a1: int, a2: int, x: int, y: int) -> int:
    """sum_{i=1}^{n} a_i^2 mod MOD，其中 a_n = x*a_{n-1} + y*a_{n-2}。"""
    if n <= 0:
        return 0
    if n == 1:
        return a1 * a1 % MOD
    # 迭代：O(n) 对本题 n <= 1e18 不可行，但纯标准库无矩阵乘法库；
    # n 较小时直接迭代，较大时用 4x4 矩阵快速幂（手写）。
    if n <= 64:
        prev2, prev1 = a1 % MOD, a2 % MOD
        s = (prev2 * prev2 + prev1 * prev1) % MOD
        for _ in range(n - 2):
            cur = (x * prev1 + y * prev2) % MOD
            s = (s + cur * cur) % MOD
            prev2, prev1 = prev1, cur
        return s
    return mat_pow_sum(n, a1, a2, x, y)


def mat_pow_sum(n: int, a1: int, a2: int, x: int, y: int) -> int:
    """状态 v = (a_n^2, a_n a_{n-1}, a_{n-1}^2, S_n) 的 4x4 矩阵快速幂。"""

    def mul(p, q):
        r = [[0] * 4 for _ in range(4)]
        for i in range(4):
            pi = p[i]
            for k in range(4):
                pik = pi[k]
                if pik:
                    qk = q[k]
                    for j in range(4):
                        r[i][j] = (r[i][j] + pik * qk[j]) % MOD
        return r

    def pow_mat(m, e):
        r = [[int(i == j) for j in range(4)] for i in range(4)]
        while e > 0:
            if e & 1:
                r = mul(r, m)
            m = mul(m, m)
            e >>= 1
        return r

    T = [
        [x * x % MOD, 2 * x * y % MOD, y * y % MOD, 0],
        [x % MOD, y % MOD, 0, 0],
        [1, 0, 0, 0],
        [x * x % MOD, 2 * x * y % MOD, y * y % MOD, 1],  # ★ S 行 = a² 行 + 1（曾是 (0,0,0,1) 的 bug）
    ]
    P = pow_mat(T, n - 2)
    a1m, a2m = a1 % MOD, a2 % MOD
    v0 = a2m * a2m % MOD
    v1 = a2m * a1m % MOD
    v2 = a1m * a1m % MOD
    v3 = (v0 + v2) % MOD
    row = P[3]
    return (row[0] * v0 + row[1] * v1 + row[2] * v2 + row[3] * v3) % MOD


if __name__ == '__main__':
    solve()
