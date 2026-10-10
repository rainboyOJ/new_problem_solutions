#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:45
# update_at: 2026-10-08 03:45

import sys

# 斐波那契串 S[i] 的跨界贡献 cross[i] 从 i >= K+3 起只随 i 的奇偶取两个定值，
# 所以递推按"步长 2"做，状态是列向量 (f[e+2k], f[e+2k+1], 1)^T。
STEP = 2           # 递推步长 = cross 的周期
NEED_AHEAD = 5     # 在 K 之外多构造几项，够容斥反推两个常数即可

# 类型别名（Python 3.12+ 的 type 语句）：3x3 转移矩阵，行优先
type Matrix = list[list[int]]


def prefix_function(t: str) -> list[int]:
    """t 的前缀函数（失配数组），pi[i] = t[0..i] 的最长真前后缀长度。"""
    pi = [0] * len(t)
    for i in range(1, len(t)):
        j = pi[i - 1]
        while j and t[i] != t[j]:
            j = pi[j - 1]
        if t[i] == t[j]:
            j += 1
        pi[i] = j
    return pi


def count_occ(s: str, t: str, pi: list[int], m: int) -> int:
    """t 在 s 中作为子串的出现次数（允许重叠），O(|s|)。"""
    if len(s) < m:
        return 0
    cnt = j = 0
    for ch in s:
        while j and ch != t[j]:
            j = pi[j - 1]
        if ch == t[j]:
            j += 1
        if j == m:
            cnt += 1
            j = pi[j - 1]
    return cnt


def mat_mul(x: Matrix, y: Matrix, mod: int) -> Matrix:
    """3x3 矩阵乘法后取模。"""
    r = [[0] * 3 for _ in range(3)]
    for i in range(3):
        for k in range(3):
            xa = x[i][k]
            if not xa:
                continue
            for j in range(3):
                r[i][j] = (r[i][j] + xa * y[k][j]) % mod
    return r


def mat_pow(b: Matrix, e: int, mod: int) -> Matrix:
    """3x3 矩阵快速幂，O(log e) 次矩阵乘法。"""
    r = [[int(i == j) for j in range(3)] for i in range(3)]
    while e:
        if e & 1:
            r = mat_mul(r, b, mod)
        b = mat_mul(b, b, mod)
        e >>= 1
    return r


def fib_count(n: int, m: int, p: int, t: str) -> int:
    """T 在 S[n] 中的出现次数模 p：小 n 暴力打表，大 n 走矩阵快速幂。"""
    pi = prefix_function(t)
    # 题面把 S[1] 写成 "0" 是笔误（那样全串皆 0），按样例与真实数据应为 S[0]="0", S[1]="1"
    seq = ["0", "1"]
    while len(seq[-1]) < m - 1:
        seq.append(seq[-2] + seq[-1])
    # K = 最小的下标使 |S[K]| >= M-1；从 K 起前后缀长度足够，跨界形态才稳定
    k = next(i for i, si in enumerate(seq) if len(si) >= m - 1)

    need = min(n, k + NEED_AHEAD)                 # 小 N 时得把 S[n] 也拼出来
    while len(seq) - 1 < need:
        seq.append(seq[-2] + seq[-1])
    f = [count_occ(si, t, pi, m) for si in seq]   # f[i] = T 在 S[i] 中的精确次数（不取模）

    if n <= need:                                 # 已经能直接回答，不进矩阵
        return f[n] % p

    e = k + 3 if (k + 3) % STEP == 0 else k + 4   # 第一个 >= K+3 的偶下标
    a0, b0 = f[e], f[e + 1]
    c_even = f[e] - f[e - 1] - f[e - 2]           # 偶数步的跨界次数 cross[e]
    c_odd = f[e + 1] - f[e] - f[e - 1]            # 奇数步的跨界次数 cross[e+1]

    # a' = a + b + c_even, b' = a + 2b + c_even + c_odd，第三列 1 承载常数项
    base = [[1, 1, c_even], [1, 2, c_even + c_odd], [0, 0, 1]]
    r = mat_pow(base, (n - e) // STEP, p)
    va = (r[0][0] * a0 + r[0][1] * b0 + r[0][2]) % p   # f[n]，n 与 e 同奇偶
    vb = (r[1][0] * a0 + r[1][1] * b0 + r[1][2]) % p   # f[n]，n 与 e 奇偶不同
    return va if (n - e) % STEP == 0 else vb


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m, p = next(data), next(data), next(data)
    t = next(data).decode()
    print(fib_count(int(n), int(m), int(p), t))


if __name__ == "__main__":
    solve()
