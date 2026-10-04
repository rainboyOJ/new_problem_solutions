#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 01:50
# update_at: 2026-10-01 02:01

import sys


def suffix_lengths(seq: list[int]) -> list[int]:
    """g[i] = 以 seq[i] 开头的最长不下降子序列长度 = 1 + max{g[j] : j > i 且 seq[j] >= seq[i]}。"""
    g = [1] * len(seq)
    for i in range(len(seq) - 1, -1, -1):  # 倒着算，用到的 g[j] 都已就绪
        g[i] = 1 + max((g[j] for j in range(i + 1, len(seq)) if seq[j] >= seq[i]), default=0)
    return g


def lex_smallest(seq: list[int], g: list[int]) -> list[int]:
    """在全部最长不下降子序列中挑出字典序最小的那一条。

    每一步在候选下标里取值最小的元素：候选 = 下标在当前之后、值不小于已选末尾、
    且以它开头的 g 值还够长（g[j] >= 剩余个数）。够长保证后面一定能补齐，
    取最小保证本位最小；并列时 min 保留最靠前的下标，留给后面的选择最多。
    """
    picked: list[int] = []
    start = 0                      # 下一个元素只能从 start 及之后取
    lower: int | None = None       # 已选末尾的值；None 表示还没选过，不受下界限制
    need = max(g)                  # 还差几个元素才够最长
    while need:
        j = min(
            (j for j in range(start, len(seq))
             if g[j] >= need and (lower is None or seq[j] >= lower)),
            key=seq.__getitem__,
        )
        picked.append(seq[j])
        start, lower, need = j + 1, seq[j], need - 1
    return picked


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 题面的序列长度
    seq = [next(data) for _ in range(n)]

    g = suffix_lengths(seq)
    ans = lex_smallest(seq, g)
    print(len(ans))
    print(*ans)


if __name__ == "__main__":
    solve()
