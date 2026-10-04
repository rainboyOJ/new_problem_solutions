#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 13:29
# update_at: 2026-10-01 13:29

import sys
from math import isqrt


def packing_min(k: int) -> tuple[list[int], list[int]]:
    """占满 k 层时体积与侧面积的绝对下界前缀和：从下往上第 j 层至少有半径、高度 j。

    k 层的半径必须严格递减，所以再省也要占到 1,2,...,k 这些半径，高度同理；
    于是 min_v[k] = sum(j^3)、min_s[k] = sum(2*j^2) 就是剩余层数对应的最小值。
    """
    min_v = [0] * (k + 1)
    min_s = [0] * (k + 1)
    for j in range(1, k + 1):
        min_v[j] = min_v[j - 1] + j ** 3
        min_s[j] = min_s[j - 1] + 2 * j ** 2
    return min_v, min_s


def solve() -> None:
    """自底向上 DFS 枚举每层的 (R, H)，用三条下界剪枝，取最小的 S。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    min_v, min_s = packing_min(m)
    if min_v[m] > n:  # 连最省体积的 1,2,...,m 都塞不进 N，直接无解
        print(0)
        return

    # 任意可行方案的 S <= 3N（见正文证明），取 3N+1 当"无解"哨兵，也当剪枝的初始上界
    inf = 3 * n + 1
    best = inf

    def dfs(level: int, vol: int, area: int, r_max: int, h_max: int) -> None:
        """已放好 level-1 层、占用体积 vol、侧面积 area，下一层半径、高度上界为 r_max/h_max。"""
        nonlocal best
        left = m - level + 1  # 含本层在内还要放几层
        rest = n - vol        # 还要填的体积

        if area + min_s[left] >= best:  # 下界一：剩余层的侧面积不可能比 min_s 更小
            return
        # 下界二：剩余体积的侧面积至少是 2*rest/r_max（把余下体积摊成一根半径 r_max 的柱），
        # 通分后避免除法与浮点误差。
        if area * r_max + 2 * rest >= best * r_max:
            return

        if left == 1:  # 最后一层：体积必须整除 r^2，直接算高度，不必再开一层递归
            for r in range(r_max, 0, -1):
                square = r * r
                if rest % square:
                    continue
                h = rest // square
                if h > h_max:
                    continue
                area_now = area + 2 * r * h + (square if level == 1 else 0)
                if area_now < best:
                    best = area_now
            return

        for r in range(r_max, left - 1, -1):  # 本层半径至少 left，否则上面放不下 left-1 层
            square = r * r
            base = area + (square if level == 1 else 0)  # 顶面积只在下底面那一层计入
            if base * r + 2 * rest >= best * r:  # 同样的侧面积下界，先从 r 上砍掉
                continue
            # 本层高度留给上层 min_v[left-1] 的体积，上界由此收紧
            h_top = min(h_max, (rest - min_v[left - 1]) // square)
            for h in range(h_top, left - 1, -1):
                area_now = base + 2 * r * h
                if area_now + min_s[left - 1] >= best:  # 本层定下后重新估一次下界
                    continue
                dfs(level + 1, vol + square * h, area_now, r - 1, h - 1)

    dfs(1, 0, 0, isqrt(n), n)
    print(0 if best == inf else best)


if __name__ == "__main__":
    solve()
