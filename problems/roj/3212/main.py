#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 13:44
# update_at: 2026-10-09 13:44

import sys
from math import sqrt

type Point = tuple[int, int]   # 前哨站坐标


def find_root(pa: list[int], x: int) -> int:
    """并查集找根，带路径压缩（写成迭代，避免深递归）。"""
    root = x
    while pa[root] != root:
        root = pa[root]
    while pa[x] != root:
        pa[x], x = root, pa[x]
    return root


def min_radius(s: int, p: int, pts: list[Point]) -> float:
    """通信半径最小值：完全图 MST 中第 P-S 小的边权（S 是卫星信道数）。"""
    edges: list[tuple[float, int, int]] = sorted(
        (sqrt((pts[i][0] - pts[j][0]) ** 2 + (pts[i][1] - pts[j][1]) ** 2), i, j)
        for i in range(p)
        for j in range(i + 1, p)
    )

    pa = list(range(p))
    need = p - s            # 连通块 1 个点降到 S 个，需要加入 P-S 条边
    if need <= 0:           # P <= S 时全部点用卫星直连，半径为 0
        return 0.0
    ans = 0.0
    added = 0
    for w, u, v in edges:
        ru, rv = find_root(pa, u), find_root(pa, v)
        if ru != rv:
            pa[ru] = rv
            ans = w             # 最后加入的这条边就是瓶颈边
            added += 1
            if added == need:
                break
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        t = next(data)
    except StopIteration:   # 空输入直接退出，不抛异常
        return

    out: list[str] = []
    for _ in range(t):
        s, p = next(data), next(data)
        pts: list[Point] = [(next(data), next(data)) for _ in range(p)]
        out.append(f"{min_radius(s, p, pts):.2f}")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
