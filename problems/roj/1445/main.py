#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 10:50
# update_at: 2026-09-30 10:50

import sys
from functools import cache

INF = 10**9


def build_pre_masks(rects: list[tuple[int, int, int, int, int]]) -> list[int]:
    """计算每个矩形必须在哪些矩形之后涂色：返回先决条件位掩码。

    当矩形 u 的下边界与矩形 v 的上边界贴合且水平区间重叠时，u 是 v 的直接上方矩形。
    """
    return [
        sum(
            1 << u
            for u, (uy1, ux1, uy2, ux2, _) in enumerate(rects)
            if uy2 == vy1 and not (ux2 <= vx1 or ux1 >= vx2)
        )
        for vy1, vx1, _, vx2, _ in rects
    ]


def min_brush_switches(n: int, rects: list[tuple[int, int, int, int, int]], pre_mask: list[int]) -> int:
    """记忆化搜索求涂满所有矩形的最少拿起刷子次数。"""
    target = (1 << n) - 1

    @cache
    def dfs(mask: int, cur_color: int) -> int:
        if mask == target:
            return 0

        # 当前可涂且与 cur_color 同色的矩形集合
        same_color = [
            i
            for i in range(n)
            if not (mask >> i & 1) and (mask & pre_mask[i]) == pre_mask[i] and rects[i][4] == cur_color
        ]
        if same_color:
            # 贪心：若手上有刷子且有同色可用，立刻全部涂掉不增加换刷次数
            nxt_mask = mask
            for i in same_color:
                nxt_mask |= 1 << i
            return dfs(nxt_mask, cur_color)

        # 换新颜色刷子：尝试所有当前上方依赖已全部涂好的可用颜色
        available = [
            i
            for i in range(n)
            if not (mask >> i & 1) and (mask & pre_mask[i]) == pre_mask[i]
        ]
        colors = {rects[i][4] for i in available}
        return min((1 + dfs(mask, c) for c in colors), default=INF)

    return dfs(0, 0)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    tokens = list(data)
    if not tokens:
        return
    it = iter(tokens)
    n = next(it)
    # y1, x1, y2, x2, color
    rects = [
        (next(it), next(it), next(it), next(it), next(it))
        for _ in range(n)
    ]
    pre_mask = build_pre_masks(rects)
    ans = min_brush_switches(n, rects, pre_mask)
    print(ans)


if __name__ == "__main__":
    solve()
