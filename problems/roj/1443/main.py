#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:00
# update_at: 2026-07-05 22:00

import sys
from functools import lru_cache


def min_depth(n: int) -> int:
    """n=1..n*2 的最优链长预计算不了，这里只给出深度下界：每步最多翻倍。"""
    d = 0
    v = 1
    while v < n:
        v *= 2
        d += 1
    return d


def search(chain: list[int], used: set[int], depth: int, n: int) -> list[int] | None:
    """在剩余 depth 步内把链延伸到 n；找到即返回整条链，否则返回 None。"""
    last = chain[-1]
    if last == n:
        return chain
    # 剪枝一：每步最多翻倍，翻 depth 倍也够不到 n
    if last << depth < n:
        return None

    # 候选新值 = 前面的数两两之和（i、j 可相等，含翻倍），从大到小尝试以贪心逼近 n
    m = len(chain)
    cands = sorted({chain[i] + chain[j] for i in range(m) for j in range(i + 1)}, reverse=True)
    lower = max(-(-n >> (depth - 1)), last + 1)         # 須大于 last，且剩 depth-1 步翻倍须够到 n
    for v in cands:
        if v < lower:
            break                                       # cands 从大到小，后面只会更小
        if v > n or v in used:
            continue
        chain.append(v)
        used.add(v)
        res = search(chain, used, depth - 1, n)
        if res is not None:
            return res
        chain.pop()
        used.remove(v)

    return None


def solve_one(n: int) -> list[int]:
    """迭代加深：链长从下界开始逐层加深，第一条找到的链就是最短链。"""
    if n == 1:
        return [1]
    for depth in range(min_depth(n), 23):
        res = search([1], {1}, depth, n)
        if res is not None:
            return res
    raise AssertionError("n 太大，深度上限 22 不够")


def solve() -> None:
    out: list[str] = []
    for token in sys.stdin.buffer.read().split():
        n = int(token)
        if n == 0:
            break
        out.append(' '.join(map(str, solve_one(n))))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
