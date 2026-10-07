#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 10:20
# update_at: 2026-10-07 10:20

import sys
from collections import deque

MOD = 10 ** 9 + 7  # 答案取模的质数
ALPHA = 26         # 字母表大小
LOWER = 97         # ord('a')

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Dfa = list[list[int]]   # 补全后的 DFA 转移表 goto[u][c]：状态 u 收到字母 c 后到达的状态
type Matrix = list[list[int]]  # 增广矩阵，每行 = k 个系数 + 末尾 1 个常数项


def build_dfa(patterns: list[bytes]) -> tuple[Dfa, list[bool]]:
    """把模式串建成 AC 自动机，返回（补全后的 DFA 转移表, 已命中标记）。

    term[u] 为真表示「从根走到 u 的这条路径上，某个模式串是它的后缀」——一旦到达这种状态
    就说明已经有 S_i 出现在 T 里了，游戏结束。标记沿 fail 链传播。
    """
    trie = [[-1] * ALPHA]  # -1 表示该字母没有儿子
    term = [False]
    for p in patterns:
        u = 0
        for c in p:
            c -= LOWER
            if trie[u][c] < 0:
                trie[u][c] = len(trie)
                trie.append([-1] * ALPHA)
                term.append(False)
            u = trie[u][c]
        term[u] = True

    size = len(trie)
    goto: Dfa = [[0] * ALPHA for _ in range(size)]  # 0 是根，缺儿子时失配回根
    fail = [0] * size
    for c in range(ALPHA):
        v = trie[0][c]
        goto[0][c] = v if v > 0 else 0

    dq = deque(v for v in goto[0] if v > 0)  # 根的儿子的 fail 都是根
    while dq:
        u = dq.popleft()
        if term[fail[u]]:
            term[u] = True  # fail 链上有模式串结尾 → 自己也已经命中
        gu, gf = goto[u], goto[fail[u]]  # fail[u] 层次更浅，其 goto 行已算好
        for c in range(ALPHA):
            v = trie[u][c]
            if v > 0:
                fail[v] = gf[c]
                gu[c] = v
                dq.append(v)
            else:
                gu[c] = gf[c]  # 失配转移，补全成 DFA
    return goto, term


def first_hit_expectation(goto: Dfa, term: list[bool]) -> int:
    """求从根出发、首次命中的期望步数（模 MOD）。

    设 E[u] = 从状态 u（尚未命中）出发还需敲的字符数期望，则每敲一个字符必 +1：
        E[u] = 1 + (1/26) * Σ_c (goto[u][c] 已命中 ? 0 : E[goto[u][c]])
    两边乘 26 得 26*E[u] - Σ_{未命中的后继} E[后继] = 26，是 k 元线性方程组。
    终止态的期望恒为 0，不给它设未知量，故未知量个数 k = 非终止状态数 ≤ 1 + Σ|S_i| ≤ 151。
    """
    ids = [-1] * len(goto)  # 自动机状态 -> 未知量下标；-1 表示终止态
    k = 0
    for u in range(len(goto)):
        if not term[u]:
            ids[u] = k
            k += 1
    if ids[0] < 0:
        return 0  # 根就是终止态（存在空模式串）时无需敲任何字符；题面保证 |S_i| >= 1

    mat: Matrix = [[0] * (k + 1) for _ in range(k)]
    for i in range(k):
        mat[i][i] = ALPHA
        mat[i][k] = ALPHA
    for u in range(len(goto)):
        i = ids[u]
        if i < 0:
            continue
        row = mat[i]
        for c in range(ALPHA):
            j = ids[goto[u][c]]
            if j >= 0:
                row[j] -= 1  # 命中后继的期望按 0 计，不入方程
    for row in mat:
        for j in range(k + 1):
            row[j] %= MOD

    for col in range(k):  # 前向消元，主元列归一化
        piv = col
        while piv < k and mat[piv][col] == 0:
            piv += 1
        if piv == k:
            continue  # 不可达：命中必然会发生，系数矩阵非奇异
        if piv != col:
            mat[col], mat[piv] = mat[piv], mat[col]
        pc = mat[col]
        inv = pow(pc[col], MOD - 2, MOD)
        for r in range(col + 1, k):
            pr = mat[r]
            f = pr[col] * inv % MOD
            if f:
                pr[col:] = [(a - f * b) % MOD for a, b in zip(pr[col:], pc[col:])]
        pc[col:] = [v * inv % MOD for v in pc[col:]]

    x = [0] * k  # 回代：主元行已归一化，x[i] = 常数项 - Σ 已知项
    for i in range(k - 1, -1, -1):
        row = mat[i]
        x[i] = (row[k] - sum(row[j] * x[j] for j in range(i + 1, k))) % MOD
    return x[0]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    T = int(next(data))
    out: list[str] = []
    for _ in range(T):
        n = int(next(data))
        patterns = [next(data) for _ in range(n)]
        goto, term = build_dfa(patterns)
        out.append(str(first_hit_expectation(goto, term)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
