#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 22:35
# update_at: 2026-10-01 22:35

import sys


def unfold(s: str, i: int, j: int, cut: list[list[int]], rep: list[list[int]]) -> str:
    """按 DP 记录的决策还原 s[i..j] 的最优折叠串：rep 优先，其次按 cut 拆两半。"""
    if i == j:
        return s[i]
    p = rep[i][j]
    if p:  # 整段是一个短块重复 length/p 次，块内继续递归折叠
        cnt = (j - i + 1) // p
        return f"{cnt}({unfold(s, i, i + p - 1, cut, rep)})"
    k = cut[i][j]
    return unfold(s, i, k, cut, rep) + unfold(s, k + 1, j, cut, rep)


def fold(s: str) -> str:
    """区间 DP 求 s 的最短折叠串：先枚举断点拼接，再看整段能否写成 X(...)。"""
    n = len(s)
    f = [[0] * n for _ in range(n)]     # f[i][j]：s[i..j] 展开前的最少字符数
    cut = [[-1] * n for _ in range(n)]  # 拼接时的断点：左半段的右端点
    rep = [[0] * n for _ in range(n)]   # 折叠时的块长 p，0 表示这一段不整体折叠
    for i in range(n):
        f[i][i] = 1                      # 单个字母只能是自己

    for length in range(2, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            # 拼接（定义 2）：枚举断点，左右两半各自最优
            k = min(range(i, j), key=lambda k: f[i][k] + f[k + 1][j])
            f[i][j] = f[i][k] + f[k + 1][j]
            cut[i][j] = k
            # 折叠（定义 3）：枚举块长 p，要求 p 整除 length 且相邻块完全相同；
            # 折叠串是 "重复次数(块的最优折叠)"，所以要额外付出位数 + 一对括号
            for p in range(1, length // 2 + 1):
                if length % p or s[i:j + 1 - p] != s[i + p:j + 1]:
                    continue             # 整段每隔 p 个字符与前面相同，才以 p 为循环节
                total = f[i][i + p - 1] + len(str(length // p)) + 2
                if total < f[i][j]:      # 严格更短才改写决策，平手时保留拼接
                    f[i][j], rep[i][j] = total, p
    return unfold(s, 0, n - 1, cut, rep)


def solve() -> None:
    s = sys.stdin.read().strip()
    print(fold(s))


if __name__ == "__main__":
    solve()
