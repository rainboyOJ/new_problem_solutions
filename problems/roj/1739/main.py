#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:29
# update_at: 2026-10-07 20:33

import sys

DAY = 24            # 每天 24 小时，接续等待只由 (l_e + d_e) 与 l_f 对 24 取模决定
INF = 10**18        # 「这个配对下连不成单环」的哨兵

type InEdges = list[list[int]]  # InEdges[v] = 终点是车站 v 的两条线路编号


def wait_cost(dep: list[int], dur: list[int], e: int, f: int) -> int:
    """在 e 号线路到站后接续 f 号线路要等的时长（与已经过了几天无关）。"""
    return (dep[f] - dep[e] - dur[e]) % DAY


def shortest_tour(dep: list[int], dur: list[int], ins: InEdges, first: int) -> int:
    """固定 1 号车站两种配对中的第 first 种，返回坐遍所有线路回到 1 号站的最短用时。"""
    n = len(ins)
    m = 2 * n
    succ = [0] * m                      # succ[r] = 到达车站后接着乘坐的线路
    a, b = ins[0]                       # 1 号车站的两条入边，两条出边是线路 0、1
    succ[a], succ[b] = (1, 0) if first else (0, 1)

    base = 0                            # 其余车站都取当地更省的配对时的等待之和
    delta = [0] * n                     # 车站 v 翻转配对要多花的等待
    for v in range(1, n):
        x, y = ins[v]
        ox, oy = 2 * v, 2 * v + 1       # 车站 v 的两条出边
        cost_x, cost_y = wait_cost(dep, dur, x, ox), wait_cost(dep, dur, y, oy)
        cost_swap = wait_cost(dep, dur, x, oy) + wait_cost(dep, dur, y, ox)
        if cost_x + cost_y <= cost_swap:
            succ[x], succ[y] = ox, oy
            base += cost_x + cost_y
            delta[v] = cost_swap - cost_x - cost_y
        else:
            succ[x], succ[y] = oy, ox
            base += cost_swap
            delta[v] = cost_x + cost_y - cost_swap

    ring = [-1] * m                     # 初始配对把线路拆成若干环，先逐个编号
    ring_cnt = 0
    for r in range(m):
        if ring[r] >= 0:
            continue
        cur = r
        while ring[cur] < 0:
            ring[cur] = ring_cnt
            cur = succ[cur]
        ring_cnt += 1

    # 翻转车站 v 的配对会把 ring[x]、ring[y] 两个环并成一个，代价 delta[v]；
    # 要让全部环并成一个，取环图上的最小生成树（同环的两个入边翻转只会拆环，不成边）。
    edges = []                          # （翻转代价, 被合并的两个环）
    for v in range(1, n):
        x, y = ins[v]
        if ring[x] != ring[y]:
            edges.append((delta[v], ring[x], ring[y]))
    edges.sort()

    par = list(range(ring_cnt))
    merges = extra = 0                  # 已合并次数、合并多花的等待
    for w, u, v in edges:
        while par[u] != u:              # 路径减半地找根
            par[u] = par[par[u]]
            u = par[u]
        while par[v] != v:
            par[v] = par[par[v]]
            v = par[v]
        if u != v:
            par[u] = v
            merges += 1
            extra += w
    if merges != ring_cnt - 1:
        return INF                      # 环图不连通，这个配对拿不到单环

    travel = sum(dur)                   # 行驶时长与方案无关，整块计入
    best = INF
    for s in (0, 1):
        other = 1 - s                   # 首班是线路 s，另一条入边的接续照常发生
        pin = next(r for r in (a, b) if succ[r] == other)
        total = travel + dep[s] + wait_cost(dep, dur, pin, other) + base + extra
        best = min(best, total)
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    dep, dur = [0] * (2 * n), [0] * (2 * n)  # 线路 i 的每日发车时刻 l_i 与行驶时长 d_i
    ins: InEdges = [[] for _ in range(n)]
    for i in range(2 * n):
        end, l, d = next(data), next(data), next(data)   # 题面的 e_i、l_i、d_i
        ins[end - 1].append(i)
        dep[i], dur[i] = l, d

    # 1 号车站的两种入边接法都要试，各自内部再枚举首班线路，取总用时较小者
    print(min(shortest_tour(dep, dur, ins, first) for first in (0, 1)))


if __name__ == "__main__":
    solve()
