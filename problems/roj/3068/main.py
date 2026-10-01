#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 14:12
# update_at: 2026-10-01 14:17

import sys
from heapq import heapify, heappop, heappush

# 四个方向按题目优先级排列：箱子 N、S、W、E 与人 n、s、w、e 共用这张表，下标顺序就是优先级。
DIRS = ((-1, 0), (1, 0), (0, -1), (0, 1))
PUSH_CH = dict(zip(DIRS, "NSWE"))  # 人贴着箱子时，箱子朝该方向移动一格
WALK_CH = "nswe"                   # 人单独朝 DIRS[i] 方向移动一格
INF = 1 << 60
STEP = 1 << 20  # 推箱次数左移到高位：一次整数比较就完成「先比推箱数、再比走路步数」的字典序


def backward_cost(n: int, m: int, free: list[bool], target: int, start: int) -> list[int]:
    """每个状态到「箱子停在 T」的最小代价，编码为 推箱次数 * STEP + 走路步数。

    状态编号 = 人的格子 * nm + 箱子的格子。在状态图上以所有「箱子已在 T」的状态为源点
    反向 Dijkstra：反向的人移动 = 人原先站在当前格的四邻；反向的推箱 = 推完后人站在箱子
    旧格子上，所以人原先在箱子的另一侧。反向图每条边权和正向相同，算出的即正向最优值。
    一弹出起点状态就收工：此后不会再出现更小的值，路径上其余状态的代价都已定稿。
    """
    nm = n * m
    cost = [INF] * (nm * nm)
    heap = [(0, p * nm + target) for p in range(nm) if free[p]]  # 箱子已到 T，代价 0
    for value, state in heap:
        cost[state] = value
    heapify(heap)

    while heap:
        d, state = heappop(heap)
        if cost[state] != d:  # 堆里的过期条目
            continue
        if state == start:  # 起点的最优值定稿，更小的状态都已经出堆了
            break
        box, person = state % nm, state // nm
        br, bc = divmod(box, m)
        pr, pc = divmod(person, m)
        for dr, dc in DIRS:
            # 反向的人移动：人从四邻之一的格子走到 person，那格不能被箱子占着
            nr, nc = pr + dr, pc + dc
            near = nr * m + nc
            if 0 <= nr < n and 0 <= nc < m and free[near] and near != box:
                before = near * nm + box
                if d + 1 < cost[before]:  # 走路步数 +1，落在低位
                    cost[before] = d + 1
                    heappush(heap, (d + 1, before))
            # 反向的推箱：推完后人站在箱子的旧格子上，故人原先在箱子另一侧
            if abs(br - pr) + abs(bc - pc) == 1:  # 人和箱子贴在一起才谈得上推
                opr, opc = 2 * pr - br, 2 * pc - bc  # 推之前人的格子
                if 0 <= opr < n and 0 <= opc < m and free[opr * m + opc]:
                    before = (opr * m + opc) * nm + person  # 推之前箱子正站在 person 格
                    if d + STEP < cost[before]:  # 推箱次数 +1，落在高位
                        cost[before] = d + STEP
                        heappush(heap, (d + STEP, before))
    return cost


def path_of(n: int, m: int, free: list[bool], person: int, box: int, target: int,
            cost: list[int]) -> str:
    """贴着最优值贪心还原动作串：每步挑当前优先级最高且不破坏最优性的那个动作。"""
    nm = n * m
    limit = cost[person * nm + box]
    out: list[str] = []
    spent = 0
    while box != target:
        pr, pc = divmod(person, m)
        br, bc = divmod(box, m)
        dr, dc = br - pr, bc - pc  # 人指向箱子的方向，也就是推箱方向
        # ① 能推就推：推箱字母整体排在人移动字母之前，优先级更高
        if abs(dr) + abs(dc) == 1:
            nr, nc = br + dr, bc + dc
            if 0 <= nr < n and 0 <= nc < m and free[nr * m + nc]:
                after = box * nm + nr * m + nc  # 推完之后人站到箱子原来的格子
                if spent + STEP + cost[after] == limit:  # 走这条边仍落在最优解上
                    out.append(PUSH_CH[(dr, dc)])
                    person, box, spent = box, nr * m + nc, spent + STEP
                    continue
        # ② 否则人走一步，按 n、s、w、e 的顺序取第一个可行的方向
        for i, (dr, dc) in enumerate(DIRS):
            nr, nc = pr + dr, pc + dc
            step = nr * m + nc
            if 0 <= nr < n and 0 <= nc < m and free[step] and step != box:
                if spent + 1 + cost[step * nm + box] == limit:
                    out.append(WALK_CH[i])
                    person, spent = step, spent + 1
                    break
        else:  # 不做静默死循环：进入循环时保证 spent + cost[当前状态] == limit
            raise AssertionError(f"状态 {(person, box)} 上没有紧边")
    return "".join(out)


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    index = 0
    while True:
        n, m = int(next(tokens)), int(next(tokens))
        if n == 0 and m == 0:
            break
        index += 1
        grid = b"".join(next(tokens) for _ in range(n))
        nm = n * m
        free = [ch != 35 for ch in grid]  # 35 是 '#'：墙不可进入
        person, box, target = grid.index(83), grid.index(66), grid.index(84)
        start = person * nm + box
        cost = backward_cost(n, m, free, target, start)
        if cost[start] >= INF:  # 终点状态压根没被松弛到，方案不存在
            out.append(f"Maze #{index}\nImpossible.\n")
        else:
            moves = path_of(n, m, free, person, box, target, cost)
            out.append(f"Maze #{index}\n{moves}\n")
    print("\n".join(out))


if __name__ == "__main__":
    solve()
