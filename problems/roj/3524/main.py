#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:20
# update_at: 2026-10-02 05:20

import sys
from collections.abc import Iterator


def simulate(state: list[int], adj: list[list[tuple[int, int]]], indeg: list[int]) -> None:
    """按拓扑序推进网络：兴奋（状态大于 0）的神经元把状态乘边权送给下游，
    后代收齐全部上游信号后即得到终值（阈值已在 solve 中预扣）。"""
    remain = indeg[:]  # 每个神经元还剩几个上游没处理
    ready = [i for i in range(1, len(state)) if indeg[i] == 0]
    while ready:
        u = ready.pop()
        for v, w in adj[u]:
            if state[u] > 0:  # 平静的神经元不发信号，只完成入度计数
                state[v] += state[u] * w
            remain[v] -= 1
            if remain[v] == 0:  # 上游全部处理完，可以计算 v 的最终状态
                ready.append(v)


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    n, p = next(data), next(data)

    state = [0] * (n + 1)  # 神经元状态 C_i；非输入层初值必为 0
    limit = [0] * (n + 1)  # 阈值 U_i
    for i in range(1, n + 1):
        state[i] = next(data)
        limit[i] = next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    indeg = [0] * (n + 1)
    outdeg = [0] * (n + 1)
    for _ in range(p):
        a, b, w = next(data), next(data), next(data)
        adj[a].append((b, w))
        indeg[b] += 1
        outdeg[a] += 1

    # 阈值先扣：有上游的神经元按公式减 U_i；输入层（无上游）保持题面给定的初值
    for i in range(1, n + 1):
        if indeg[i]:
            state[i] -= limit[i]

    simulate(state, adj, indeg)

    # 输出层 = 没有出边的神经元，按编号从小到大只报状态大于 0 的
    out = [f"{i} {state[i]}" for i in range(1, n + 1) if outdeg[i] == 0 and state[i] > 0]
    print('\n'.join(out) if out else 'NULL')


if __name__ == "__main__":
    solve()
