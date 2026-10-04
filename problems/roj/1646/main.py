#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:55
# update_at: 2026-10-01 00:06

import sys

ALPHABET = range(10)  # 每个 X_i 的取值范围 0..9


def build_fail(pat: list[int]) -> list[int]:
    """pat 的失配指针数组 fail[i]：pat[0:i+1] 的最长真前后缀长度。"""
    fail = [0] * (len(pat) + 1)
    for i in range(1, len(pat)):
        j = fail[i]
        while j and pat[i] != pat[j]:  # 回退到能接上 pat[i] 的最长前缀
            j = fail[j]
        fail[i + 1] = j + 1 if pat[i] == pat[j] else 0
    return fail


def build_transition(pat: list[int], fail: list[int]) -> list[list[int]]:
    """自动机转移矩阵 trans[q][q2]：已匹配 q 位时读入一个数字后匹配到 q2 位的数字个数。

    状态 m 表示"不吉利数字已出现"，是吸收态，题面禁止它出现，故不参与计数。
    """
    m = len(pat)
    trans = [[0] * (m + 1) for _ in range(m + 1)]
    for q in range(m):  # 状态 m 是吸收态，不需要从它出发的转移
        for d in ALPHABET:
            j = q
            while j and pat[j] != d:  # 失配则沿着 fail 链回退
                j = fail[j]
            nxt = j + 1 if pat[j] == d else 0
            if nxt < m:  # 只保留"还没出现完整不吉利数字"的转移
                trans[q][nxt] += 1
    return trans


def mat_mul(a: list[list[int]], b: list[list[int]], mod: int) -> list[list[int]]:
    """模 mod 的矩阵乘法：优化掉零元的稀疏乘，n,m<=20 时比 numpy 更可控。"""
    n, k, m = len(a), len(b), len(b[0])
    out = [[0] * m for _ in range(n)]
    for i in range(n):
        row = out[i]
        for t in range(k):
            if a[i][t]:  # a[i][t] 为 0 时整行贡献为 0，直接跳过
                v = a[i][t]
                b_row = b[t]
                for j in range(m):
                    row[j] = (row[j] + v * b_row[j]) % mod
    return out


def mat_pow(base: list[list[int]], exp: int, mod: int) -> list[list[int]]:
    """矩阵快速幂：对 exp 做二进制分解，反复平方。"""
    size = len(base)
    result = [[int(i == j) for j in range(size)] for i in range(size)]  # 单位矩阵
    while exp:
        if exp & 1:
            result = mat_mul(result, base, mod)
        base = mat_mul(base, base, mod)
        exp >>= 1
    return result


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n, m, mod = int(data[0]), int(data[1]), int(data[2])
    pat = [c - 48 for c in data[3]]  # 不吉利数字的 m 个十进制位（bytes 逐字节减 '0'）

    fail = build_fail(pat)
    trans = build_transition(pat, fail)

    # dp 向量：v[q] = 已经填了 i 位、当前匹配到不吉利数字前 q 位、且从未出现完整串的方案数。
    # 每填一位就是右乘一次 trans，故 n 位后 v = e_0 * trans^n，答案是不含吸收态的全部状态和。
    v = [[1] + [0] * m]  # 初始向量 e_0（行向量），未填任何位时匹配长度必然是 0
    v = mat_mul(v, mat_pow(trans, n, mod), mod)

    print(sum(v[0]) % mod)  # 状态 0..m-1 之和；状态 m 已在建矩阵时排除


if __name__ == "__main__":
    solve()
