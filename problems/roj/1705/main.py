#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 16:05
# update_at: 2026-10-07 16:05

import sys
from collections import deque

MOD = 100000   # 答案取模的模数
SHIFT = 64     # 压位矩阵乘法：每个元素占 64 位，一列最多累加 size<=101 次不会进位
MASK = (1 << SHIFT) - 1

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Matrix = list[list[int]]   # 方阵，元素已模 MOD
type Trans = list[list[int]]    # DFA 转移表，Trans[u][c] 是状态 u 走字符 c 的落点


def build_dfa(pats: list[str]) -> tuple[Trans, list[bool]]:
    """把禁止子串建成 Trie 并补全成 DFA，返回 (转移表 nxt, 危险标记 danger)。

    nxt[u][c] 是状态 u 走字符 c 的落点（缺边已用 fail 链补上）；
    danger[u] 为真表示"根到 u 的路径的某个后缀"是一个完整禁止子串。
    """
    code = {'A': 0, 'C': 1, 'T': 2, 'G': 3}   # 字符 -> 自动机字母表下标
    nxt: list[list[int]] = [[0] * 4]          # 0 号状态是根
    danger: list[bool] = [False]
    for s in pats:
        cur = 0
        for ch in s:
            v = code[ch]
            if nxt[cur][v] == 0:              # 开新点
                nxt[cur][v] = len(nxt)
                nxt.append([0] * 4)
                danger.append(False)
            cur = nxt[cur][v]
        danger[cur] = True                    # 这个状态本身就是一个禁止子串

    fail = [0] * len(nxt)
    queue = deque()
    for c in range(4):
        if nxt[0][c]:
            queue.append(nxt[0][c])           # 根的儿子失配后回根，fail 已是 0
    while queue:
        u = queue.popleft()
        if danger[fail[u]]:                   # 后缀里带禁止串，本状态也算危险
            danger[u] = True
        for c in range(4):
            v = nxt[u][c]
            if v:
                fail[v] = nxt[fail[u]][c]     # fail[u] 已补过边，可直接查表
                queue.append(v)
            else:
                nxt[u][c] = nxt[fail[u]][c]   # 补边，得到完整 DFA
    return nxt, danger


def mat_mul(x: Matrix, y: Matrix) -> Matrix:
    """方阵乘法：把 y 的每行压成一个大整数，一次整数乘法就得到结果的整行。"""
    size = len(x)
    packed = [sum(v << (SHIFT * j) for j, v in enumerate(row)) for row in y]
    out: Matrix = []
    for row in x:
        acc = 0
        for k in range(size):
            acc += row[k] * packed[k]   # 每个 64 位位段里独立累加 x[i][k]*y[k][j]
        out_row: list[int] = []
        for j in range(size):
            slot = acc >> (SHIFT * j) & MASK   # 第 j 个元素的位段
            out_row.append(slot % MOD)
        out.append(out_row)
    return out


def count_legal(nxt: Trans, danger: list[bool], n: int) -> int:
    """长度为 n 且不含禁止子串的串数：在安全状态构成的 DFA 上走 n 步的路径数。"""
    safe = [u for u in range(len(nxt)) if not danger[u]]
    index = {u: i for i, u in enumerate(safe)}    # 状态 -> 压缩编号
    size = len(safe)
    base: Matrix = [[0] * size for _ in range(size)]
    for u in safe:
        for c in range(4):
            v = nxt[u][c]
            if not danger[v]:
                base[index[u]][index[v]] += 1     # 同一对状态可能有多条字符边

    # base 的 n 次幂：第 index[0] 行之和 = 从根走 n 步落在任意安全状态的串数
    res: Matrix = [[int(i == j) for j in range(size)] for i in range(size)]
    e = n
    while e:
        if e & 1:
            res = mat_mul(res, base)
        e >>= 1
        if e:
            base = mat_mul(base, base)
    return sum(res[index[0]]) % MOD


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    m = int(next(data))
    n = int(next(data))
    pats = [next(data).decode() for _ in range(m)]

    nxt, danger = build_dfa(pats)
    root_danger = danger[0]   # 空串就命中禁止串时无解（题面不会出现，防御性判断）
    print(0 if root_danger else count_legal(nxt, danger, n))


if __name__ == "__main__":
    solve()
