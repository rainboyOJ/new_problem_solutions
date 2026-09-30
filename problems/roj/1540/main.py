#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:08
# update_at: 2026-09-30 17:08

import sys


def add(tree: list[dict[int, int]], x: int, y: int, k: int, n: int, m: int) -> None:
    """在二维树状数组中将位置 (x, y) 处的值增加 k。"""
    i = x
    while i <= n:
        row = tree[i]
        j = y
        while j <= m:
            row[j] = row.get(j, 0) + k
            j += j & -j
        i += i & -i


def query(tree: list[dict[int, int]], x: int, y: int) -> int:
    """查询左上角 (1, 1) 到 (x, y) 的前缀矩形元素和。"""
    res = 0
    i = x
    while i > 0:
        row = tree[i]
        j = y
        while j > 0:
            res += row.get(j, 0)
            j -= j & -j
        i -= i & -i
    return res


def query_rect(tree: list[dict[int, int]], a: int, b: int, c: int, d: int) -> int:
    """利用二维前缀和容斥原理求子矩阵 [a, c] x [b, d] 内的元素和。"""
    return (
        query(tree, c, d)
        - query(tree, a - 1, d)
        - query(tree, c, b - 1)
        + query(tree, a - 1, b - 1)
    )


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    it = map(int, tokens)
    n = next(it)
    m = next(it)

    tree: list[dict[int, int]] = [{} for _ in range(n + 1)]
    out: list[str] = []

    for op in it:
        if op == 1:
            x, y, k = next(it), next(it), next(it)
            add(tree, x, y, k, n, m)
        else:
            a, b, c, d = next(it), next(it), next(it), next(it)
            out.append(str(query_rect(tree, a, b, c, d)))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
