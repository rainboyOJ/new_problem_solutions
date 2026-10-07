#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:53
# update_at: 2026-10-07 18:53

import sys
from collections.abc import Iterator


def find_root(x: int, fa: list[int], val: list[int]) -> int:
    """返回 x 所在集合的根，并把路径上每点的 val 压成「值(点) − 值(根)」。

    val[i] 的含义是「值(i) − 值(fa[i])」这种相对差值，所以先沿原路求出
    total = 值(x) − 值(root)，再自 x 向根逐点把 val 改写成「对根的差值」，
    顺便把 fa 直接指向根（路径压缩）。
    """
    root = x
    while fa[root] != root:
        root = fa[root]

    total = 0                      # 值(x) − 值(root)
    node = x
    while node != root:
        total += val[node]
        node = fa[node]

    pre = 0                        # 值(x) − 值(node)
    node = x
    while node != root:
        nxt = fa[node]
        diff = total - pre         # 值(node) − 值(root)
        pre += val[node]           # 下一轮要用的「值(x) − 值(nxt)」，必须先用旧 val
        val[node] = diff
        fa[node] = root
        node = nxt
    return root


def add_constraints(n: int, k: int, data: Iterator[int], fa: list[int], val: list[int]) -> bool:
    """顺序读入 k 条限制，边判定边合并，返回所有限制能否同时满足。

    限制 (x, y, c) 统一成差值等式「值(x) − 值(n+y) = c」：同集合就核对值差，
    不同集合就按这个等式反解出根的偏移量后合并。
    """
    ok = True                          # 是否所有限制能同时满足
    for _ in range(k):
        x, y, c = next(data), next(data), next(data)
        col = n + y
        root_x, root_col = find_root(x, fa, val), find_root(col, fa, val)

        if root_x == root_col:
            # 同一集合：值差已被推出，必须恰好等于 c，否则出现环上的矛盾
            known = val[x] - val[col]
            ok = ok and known == c
        else:
            # 不同集合：把 col 的根挂到 x 的根下，偏移量由等式反解
            fa[root_col] = root_x
            val[root_col] = val[x] - val[col] - c
    return ok


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, m, k = next(data), next(data), next(data)

        # 行点 1..n 与列点 n+1..n+m 共处一张并查集；列点的「值」取 −(该列净操作数)，
        # 这样限制 (x, y, c) 就统一成差值等式「值(x) − 值(n+y) = c」。
        fa = list(range(n + m + 1))
        val = [0] * (n + m + 1)        # val[i] = 值(i) − 值(fa[i])

        out.append("Yes" if add_constraints(n, k, data, fa, val) else "No")

    print("\n".join(out))


if __name__ == "__main__":
    solve()
