#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 14:25
# update_at: 2026-10-01 14:25

import sys
from math import ceil

MAX_DEPTH = 4  # 题面保证答案一旦达到 5 就输出 "5 or more"，所以迭代加深只到 4


def wrong_links(books: tuple[int, ...]) -> int:
    """数被破坏的相邻接口：正确排列里每个数 i 应紧挨在 i-1 后面。"""
    return sum(a + 1 != b for a, b in zip(books, books[1:])) + (books[-1] != len(books))


def dfs(books: tuple[int, ...], depth: int) -> bool:
    """IDA*：剩 depth 次操作能否排好，估价值 = 坏接口数 / 3 上取整。"""
    w = wrong_links(books)
    if w == 0:
        return True
    if ceil(w / 3) > depth:  # 每取一段书最多修好 3 个接口，修不完必剪掉
        return False
    seen: set[tuple[int, ...]] = set()  # 同一节点的重复后继状态只搜一次
    n = len(books)
    for l in range(n):
        for r in range(l + 1, n):
            seg = books[l:r]
            rest = books[:l] + books[r:]
            for k in range(len(rest) + 1):
                if k == l:  # 插回原位等于没动
                    continue
                nxt = rest[:k] + seg + rest[k:]
                if nxt in seen:
                    continue
                seen.add(nxt)
                if dfs(nxt, depth - 1):
                    return True
    return False


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        books = tuple(next(data) for _ in range(n))
        # 迭代加深：第一个能排好的深度就是最少操作次数
        depth = next((d for d in range(MAX_DEPTH + 1) if dfs(books, d)), None)
        out.append(str(depth) if depth is not None else "5 or more")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
