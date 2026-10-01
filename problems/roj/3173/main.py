#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:03
# update_at: 2026-10-01 23:20

import sys
from functools import cache

SIZE: list[int] = []                    # SIZE[i]：第 i 个颜色段里有几个木块
EARLIER: list[tuple[int, ...]] = []     # EARLIER[i]：第 i 段前面同色的段号，从近到远严格递减


@cache
def f(i: int, j: int, k: int) -> int:
    """消掉颜色段 i..j 的最高分，其中段 j 那一次消除还会额外带上它右边的 k 个同色木块。

    也就是说，段 j 最终是和 (SIZE[j] + k) 个同色木块一起消掉的。k 只可能由"更右边的段
    被留到最后与 j 合并"产生，因此它一定是若干整段的木块总数。
    读的是模块级的 SIZE / EARLIER，换一组数据前必须先调用 f.cache_clear()。
    """
    if i == j:
        return (SIZE[j] + k) ** 2
    res = f(i, j - 1, 0) + (SIZE[j] + k) ** 2    # 段 j 的这次消除不牵涉 i..j-1 的任何段
    for p in EARLIER[j]:
        if p < i:
            break                                # EARLIER[j] 递减，再往前都越界了
        # 段 j 的这次消除还包含左边的同色段 p：中间那截被 p 和 j 夹住，接不到外面的木块
        tail = 0 if p == j - 1 else f(p + 1, j - 1, 0)
        cand = f(i, p, k + SIZE[j]) + tail       # 段 p 右边因此挂上 SIZE[j] + k 块
        if cand > res:
            res = cand
    return res


def score(colors: list[int]) -> int:
    """一组数据的最高分：先把相邻同色木块压成颜色段，再求 f(0, m-1, 0)。"""
    global SIZE, EARLIER
    size: list[int] = []
    earlier: list[tuple[int, ...]] = []
    seen: dict[int, list[int]] = {}      # 每个颜色已经出现过的段号，递增
    previous = 0                         # 颜色 ∈ [1, n]，哨兵 0 保证第一块不并进上一段
    for value in colors:
        if previous == value:            # 与上一块同色：并进当前段，它俩分开消只会更差
            size[-1] += 1
            continue
        earlier.append(tuple(reversed(seen.get(value, ()))))
        seen.setdefault(value, []).append(len(size))
        size.append(1)
        previous = value
    SIZE, EARLIER = size, earlier
    best = f(0, len(size) - 1, 0)
    f.cache_clear()                      # 缓存是模块级的，不清会让多组数据的内存累加
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    out: list[str] = []
    for tc in range(1, T + 1):
        n = next(data)
        out.append(f"Case {tc}: {score([next(data) for _ in range(n)])}")
    print("\n".join(out))


if __name__ == "__main__":
    solve()
