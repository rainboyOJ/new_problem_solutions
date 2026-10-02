#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:34
# update_at: 2026-10-02 09:34

import sys

INF = 10**18  # "不会发生"的事件时刻：链条上没有任何饱和站点


def next_saturated(ahead: list[int], cap: list[int]) -> list[int]:
    """sat[j] = ≥j 的最近饱和景点编号，n+1 表示 j 往后一路畅通。"""
    n = len(ahead) - 1
    sat = [n + 1] * (n + 2)
    for j in range(n, 1, -1):
        sat[j] = j if ahead[j] >= cap[j] else sat[j + 1]
    return sat


def pick_edge(sat: list[int], prefix: list[int], d: list[int], used: list[int]) -> int:
    """在还有加速名额的边里选单位收益最大的一条：收益 = 链条下游的下车人数；无正收益返回 0。"""
    best, gain = 0, 0
    for i in range(1, len(d)):
        if used[i] >= d[i]:
            continue                     # 这段已减到 0，不能再加速
        stop = sat[i + 1]                # 收益链条的终点：最近的饱和景点
        if stop >= len(prefix):          # 没有饱和站点，链到终点站
            stop = len(prefix) - 1
        gain_i = prefix[stop] - prefix[i]  # 环节 [i+1, stop] 的下车人数
        if gain_i > gain:
            best, gain = i, gain_i
    return best


def batch_limit(ahead: list[int], cap: list[int], start: int, budget: int) -> int:
    """start 段一次能批量加多少个加速器：到"第一次饱和截断收益"为止，或用完 budget。"""
    gate = INF   # 链条上游各站还能放行的提前量下限
    event = INF  # 第一次让某站恰好饱和所需的提前量
    for j in range(start + 1, len(ahead)):
        if ahead[j] >= cap[j]:
            break                        # 已饱和：本站之后链条已断，不再有新事件
        room = cap[j] - ahead[j]         # 本站还能吃下的提前量
        if room <= gate:
            event = min(event, room)     # 加满 room 本站就饱和
        gate = min(gate, room)
    return min(budget, event)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, tourists, k = next(data), next(data), next(data)
    d = [0] + [next(data) for _ in range(n - 1)]  # d[i]：景点 i → i+1 的原始车程

    wait = [0] * (n + 1)     # wait[i]：在景点 i 上车的最晚到达时刻（车要等齐）
    alight = [0] * (n + 1)   # alight[j]：在景点 j 下车的乘客数
    total_t = 0
    for _ in range(tourists):
        t, a, b = next(data), next(data), next(data)
        wait[a] = max(wait[a], t)
        alight[b] += 1
        total_t += t

    # 不加速时的到达时刻：到站后等到最晚乘客才发车
    arrive0 = [0] * (n + 1)
    for i in range(1, n):
        arrive0[i + 1] = max(arrive0[i], wait[i]) + d[i]

    # cap[i] = 等待余量：到达时刻提前量不超过它时发车跟着提前，超过的部分被等待吃掉
    cap = [0] * (n + 1)
    for i in range(2, n + 1):
        cap[i] = max(arrive0[i] - wait[i], 0)

    prefix = [0] * (n + 1)  # prefix[x] = Σ_{j≤x} alight[j]
    for j in range(2, n + 1):
        prefix[j] = prefix[j - 1] + alight[j]

    ahead = [0] * (n + 1)   # ahead[i]：第 i 段已累计提前的分钟数
    used = [0] * (n + 1)    # used[i]：第 i 段已用掉的加速器数
    remain = k

    while remain > 0:
        edge = pick_edge(next_saturated(ahead, cap), prefix, d, used)
        if edge == 0:
            break                              # 没有正收益的边，再加速也无用
        budget = min(remain, d[edge] - used[edge])
        step = batch_limit(ahead, cap, edge, budget)
        used[edge] += step
        remain -= step

        # 提前量沿链条向下游传播：每过一站最多被该站的等待余量吃掉
        delta = step
        for j in range(edge + 1, n + 1):
            room = cap[j] - ahead[j]
            ahead[j] += delta
            delta = min(delta, room)
            if delta <= 0:
                break

    base = sum(arrive0[j] * alight[j] for j in range(2, n + 1)) - total_t
    saved = sum(ahead[j] * alight[j] for j in range(2, n + 1))
    print(base - saved)


if __name__ == "__main__":
    solve()
