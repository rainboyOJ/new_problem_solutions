#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 14:58
# update_at: 2026-09-30 14:58

import heapq
import sys

INF = 10**15  # 未发现费用哨兵：单次真实总费用远小于此
DIRS = (
    (0, 1, 0),   # 右移：X 增大，免付
    (1, 0, 0),   # 下移：Y 增大，免付
    (0, -1, 1),  # 左移：X 减小，付 B
    (-1, 0, 1),  # 上移：Y 减小，付 B
)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k, fee_refuel, fee_back, fee_build = (next(data) for _ in range(5))  # N K A B C
    grid = [[next(data) for _ in range(n)] for _ in range(n)]  # 1 = 交叉点已设油库

    # 状态 (i, j, r)：车位于 (i, j)、油箱还剩 r 格油时的最小费用；起点满油入堆。
    # 油量只有 0..k 共 k+1 档，"在何处加油"并入状态后问题成为普通非负权最短路。
    dist: dict[tuple[int, int, int], int] = {(0, 0, k): 0}
    heap = [(0, 0, 0, k)]  # (费用, 行, 列, 剩余油量)

    while heap:
        cost, i, j, r = heapq.heappop(heap)
        if cost != dist.get((i, j, r)):
            continue  # 过期堆项：该状态已有更小费用
        if i == n - 1 and j == n - 1:
            print(cost)
            return

        at_station = grid[i][j] == 1
        must_refuel = at_station and r < k  # 遇油库油不满：必须先加满，不能直接离开
        nxt: list[tuple[int, int, int, int]] = []
        if at_station and r < k:
            nxt.append((i, j, k, fee_refuel))  # 加满并付 A
        elif not at_station and r < k:
            nxt.append((i, j, k, fee_build + fee_refuel))  # 增设油库付 C（不含油费 A），再加满
        if not must_refuel and r:
            # 行驶一格消耗 1 格油；倒退（X 或 Y 减小）付 B，否则免费
            nxt += [(i + di, j + dj, r - 1, fee_back if back else 0) for di, dj, back in DIRS]

        for ni, nj, nr, add in nxt:
            if not (0 <= ni < n and 0 <= nj < n):
                continue  # 网格外出界
            new_cost = cost + add
            key = (ni, nj, nr)
            if new_cost < dist.get(key, INF):
                dist[key] = new_cost
                heapq.heappush(heap, (new_cost, ni, nj, nr))


if __name__ == "__main__":
    solve()
