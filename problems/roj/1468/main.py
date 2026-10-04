#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def compute_next(s: str, n: int) -> list[int]:
    """计算 KMP 的 next 数组（nxt[i] 表示前缀 s[:i] 的最长非平凡 border 长度）。"""
    nxt = [0] * (n + 1)
    j = 0
    for i in range(1, n):
        while j > 0 and s[i] != s[j]:
            j = nxt[j]
        if s[i] == s[j]:
            j += 1
        nxt[i + 1] = j
    return nxt


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    s = next(data).decode()

    nxt = compute_next(s, n)

    # min_border[i] 记录前缀 s[:i] 的最短正 border 长度；
    # 路径压缩记忆化：若其 next 指向的子前缀已有最小 border 则直接继承，否则为其自身。
    min_border = [0] * (n + 1)
    total_period = 0
    for i in range(1, n + 1):
        if nxt[i] > 0:
            min_border[i] = min_border[nxt[i]] if min_border[nxt[i]] else nxt[i]
            total_period += i - min_border[i]

    print(total_period)


if __name__ == "__main__":
    solve()
