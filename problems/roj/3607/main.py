#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:17
# update_at: 2026-10-02 10:17

import sys


def min_levels(n: int, trains: list[list[int]]) -> int:
    """在 0/1 权混合图上求各车站的最长路：边 (u → v, w) 表示 level[v] ≥ level[u] + w。

    约束：车次停靠站 y、途经但不停的中间站 x，则 x 至少比该车次每个停靠站低 1 级。
    逐对连边是 O(中间站数 × 停靠站数)，改用每车次一个虚拟节点（hub）压缩成两条
    传递边：中间站 → hub(+1) → 每个停靠站(+0)，与逐对连边完全等价。
    """
    total = n + len(trains)
    adj: list[list[int]] = [[] for _ in range(total + 1)]  # 只存终点，权由源点类型决定
    indeg = [0] * (total + 1)

    for i, stops in enumerate(trains, 1):
        hub = n + i                          # 第 i 趟车次的虚拟节点
        stop_set = set(stops)
        first, last = stops[0], stops[-1]    # 始发站与终点站
        for station in range(first, last + 1):
            if station in stop_set:
                adj[hub].append(station)     # hub → 停靠站，权 0：级别至少追平 hub
                indeg[station] += 1
            else:
                adj[station].append(hub)     # 中间站 → hub，权 1：比全部停靠站低 1 级
                indeg[hub] += 1

    level = [1] * (total + 1)                # 所有节点起评 1 级（级别最低为 1）
    queue = [u for u in range(1, total + 1) if indeg[u] == 0]
    while queue:
        u = queue.pop()
        out_w = 1 if u <= n else 0           # 车站出边压 1 级，hub 出边只下传下界
        for v in adj[u]:
            if level[v] < level[u] + out_w:
                level[v] = level[u] + out_w
            indeg[v] -= 1
            if indeg[v] == 0:                # 全部前驱定级后才出队
                queue.append(v)

    return max(level[1:n + 1])                # 虚拟节点不计入答案


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    trains: list[list[int]] = []
    for _ in range(m):
        stop_count = next(data)              # 题面的 s_i
        trains.append([next(data) for _ in range(stop_count)])

    print(min_levels(n, trains))


if __name__ == "__main__":
    solve()
