#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 10:00
# update_at: 2026-10-09 16:30

import sys

INFTY = 10 ** 9  # 答案上界：4 个矩形各自最多铺满 500x500 的整块平面

type Rect = list[int]    # [min_x, max_x, min_y, max_y, used]
type Rects = list[Rect]


def solve() -> None:
    """DFS 枚举每个点归到哪个矩形，带合法性 / 最优性 / 对称性三重剪枝。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n, k = next(data), next(data)
    except StopIteration:
        return  # 空输入
    pts = sorted((next(data), next(data)) for _ in range(n))  # 近邻点先归到一起

    rects: Rects = [[0, 0, 0, 0, False] for _ in range(k)]
    best = INFTY

    def dfs(u: int) -> None:
        nonlocal best
        cur = sum((r[1] - r[0]) * (r[3] - r[2]) for r in rects if r[4])
        if cur >= best:
            return  # 面积只会越加越大，不可能更优
        if u == n:
            best = cur
            return

        x, y = pts[u]
        for i, r in enumerate(rects):
            was_empty = not r[4]  # 空矩形彼此等价，用于对称性剪枝
            backup = r[:]
            if was_empty:
                r[0] = r[1] = x
                r[2] = r[3] = y
                r[4] = True
            else:
                r[0], r[1] = min(r[0], x), max(r[1], x)
                r[2], r[3] = min(r[2], y), max(r[3], y)

            # 相交，或边线与顶点相碰 —— 题面要求「完全分开」，接触也算冲突
            clash = any(r[0] <= o[1] and o[0] <= r[1] and r[2] <= o[3] and o[2] <= r[3]
                        for j, o in enumerate(rects) if j != i and o[4])
            if not clash:
                dfs(u + 1)

            r[:] = backup  # 恢复现场
            if was_empty:
                break  # 只试第一个空矩形

    dfs(0)
    print(best)


if __name__ == "__main__":
    solve()
