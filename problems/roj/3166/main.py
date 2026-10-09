#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 09:30
# update_at: 2026-10-09 12:52

import sys

ALPHA = 26

type Grid = list[list[int]]   # DP 表 / 字符跳转表，都是「下标 -> 下标」的二维数组


def build_next_table(s: str) -> Grid:
    """nxt[p][c] = 下标 >= p 处第一个字符 c 的位置；不存在记 len(s)。"""
    n = len(s)
    nxt: Grid = [[n] * ALPHA for _ in range(n + 1)]
    for p in range(n - 1, -1, -1):
        for c in range(ALPHA):
            nxt[p][c] = p if ord(s[p]) - 97 == c else nxt[p + 1][c]
    return nxt


def build_lcs_table(a: str, b: str) -> Grid:
    """dp[i][j] = a[i:] 与 b[j:] 的最长公共子序列长度（后缀型）。"""
    n, m = len(a), len(b)
    dp: Grid = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        row, below = dp[i], dp[i + 1]
        for j in range(m - 1, -1, -1):
            row[j] = below[j + 1] + 1 if a[i] == b[j] else max(below[j], row[j + 1])
    return dp


def all_lcs(a: str, b: str) -> list[str]:
    """按字典序返回 a、b 的全部不同最长公共子序列。

    dp 取后缀型，于是可以从前往后拼：每一位按 a~z 挑字符 c，取 c 在两侧的
    首次出现，并要求取完之后两侧剩余部分恰好还能凑出 remain - 1 个字符。
    同一个字符串只有一种走法（每位都取最靠前的那次出现），所以不会重复枚举。
    """
    n, m = len(a), len(b)
    dp = build_lcs_table(a, b)
    nxt_a = build_next_table(a)
    nxt_b = build_next_table(b)
    routes: list[str] = []

    def dfs(pos_a: int, pos_b: int, remain: int, tail: str) -> None:
        """pos_a、pos_b 是两侧下一个可用下标，remain 是还要选的字符数。"""
        if remain == 0:
            routes.append(tail)
            return
        for c in range(ALPHA):
            ia = nxt_a[pos_a][c]
            ib = nxt_b[pos_b][c]
            # 取到 c 之后仍在最优路径上：剩余部分必须还能凑出 remain - 1 个
            if ia < n and ib < m and dp[ia + 1][ib + 1] == remain - 1:
                dfs(ia + 1, ib + 1, remain - 1, tail + chr(97 + c))

    dfs(0, 0, dp[0][0], "")
    return routes              # 逐位按 a~z 枚举 ⇒ 天然字典序，无需再排序


def solve() -> None:
    tokens = sys.stdin.read().split()
    out: list[str] = []
    # 每两行一组「爱丽丝 / 鲍勃」，奇数个 token 时最后一行丢弃
    for a, b in zip(tokens[::2], tokens[1::2]):
        out += all_lcs(a, b)
    if out:
        print("\n".join(out))


if __name__ == "__main__":
    solve()
