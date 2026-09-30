#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

# 边信息类型：(u, v, weight)
Edge = tuple[int, int, int]


def kruskal(n: int, whites: list[Edge], blacks: list[Edge], bonus: int) -> tuple[int, int]:
    """计算给白边增加 bonus 权值后的最小生成树白边数与总权值。

    同权时优先选白边，便于二分出满足 need 条白边的最小额外偏移。
    """
    parent = list(range(n))

    def find(x: int) -> int:
        curr = x
        while parent[curr] != curr:
            curr = parent[curr]
        while x != curr:
            parent[x], x = curr, parent[x]
        return curr

    # 双指针归并白边（带 bonus）与黑边，因两组各自有序，归并只需 O(E)
    total_weight = white_cnt = chosen = 0
    w_idx = b_idx = 0
    w_len, b_len = len(whites), len(blacks)

    while chosen < n - 1 and (w_idx < w_len or b_idx < b_len):
        take_white = (
            b_idx >= b_len
            or (
                w_idx < w_len
                and whites[w_idx][2] + bonus <= blacks[b_idx][2]  # 权值相同时白边优先
            )
        )

        u, v, w, is_white = (
            (whites[w_idx][0], whites[w_idx][1], whites[w_idx][2] + bonus, 1)
            if take_white
            else (blacks[b_idx][0], blacks[b_idx][1], blacks[b_idx][2], 0)
        )
        if take_white:
            w_idx += 1
        else:
            b_idx += 1

        ru, rv = find(u), find(v)
        if ru != rv:
            parent[ru] = rv
            total_weight += w
            white_cnt += is_white
            chosen += 1

    return white_cnt, total_weight


def solve() -> None:
    raw = sys.stdin.buffer.read().split()
    if not raw:
        return
    data = iter(raw)
    n, m, need = int(next(data)), int(next(data)), int(next(data))

    whites: list[Edge] = []
    blacks: list[Edge] = []
    for _ in range(m):
        u, v, c, col = int(next(data)), int(next(data)), int(next(data)), int(next(data))
        if col == 0:
            whites.append((u, v, c))
        else:
            blacks.append((u, v, c))

    whites.sort(key=lambda e: e[2])
    blacks.sort(key=lambda e: e[2])

    # WQS 二分 / 带权二分：二分白边额外权值 bonus ∈ [-105, 105]
    low, high = -105, 105
    best_bonus = 0
    while low <= high:
        mid = (low + high) // 2
        cnt, _ = kruskal(n, whites, blacks, mid)
        if cnt >= need:  # 白边选多了或恰好，说明 bonus 还可以更大（惩罚不够或恰好）
            best_bonus = mid
            low = mid + 1
        else:
            high = mid - 1

    _, total = kruskal(n, whites, blacks, best_bonus)
    # 真实最优生成树权值和 = 调整后的生成树权值和 - need * best_bonus
    ans = total - need * best_bonus
    print(ans)


if __name__ == "__main__":
    solve()
