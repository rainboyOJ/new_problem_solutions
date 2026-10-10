#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:36
# update_at: 2026-10-07 15:54

import sys
from collections import deque
from collections.abc import Iterator

# 状态编码：state[i] 是结点 i+1 当前持有的权值序号。权值越大序号越小（最大权值为 0），
# 于是「父亲的序号小于儿子的序号」就是大根堆性质，和权值的具体数值无关。
type State = tuple[int, ...]        # 整棵树的当前权值排列
type Swaps = list[tuple[int, int]]  # 所有交换方式，统一写成 0 基下标且前者更小


def is_heap(state: State, fa: list[int], n: int) -> bool:
    """state 是否已满足大根堆性质：每个非根结点的序号都小于其父亲的序号。"""
    return all(state[fa[i] - 1] < state[i - 1] for i in range(1, n + 1) if fa[i])


def encode(weights: list[int], n: int) -> State:
    """把点权换成序号排列：最小权值的序号是 n-1，最大权值是 0。"""
    by_weight = sorted(zip(weights, range(1, n + 1)))  # 结点按权值升序
    rank = {node: n - 1 - pos for pos, (_, node) in enumerate(by_weight)}
    return tuple(rank[node] for node in range(1, n + 1))


def expand(state: State, swaps: Swaps) -> Iterator[State]:
    """逐个产出 state 经过一次交换能到达的排列。"""
    for i, j in swaps:
        # 交换第 i、j 位：切片拼出「前半段 + j 的值 + 中间段 + i 的值 + 后半段」
        yield state[:i] + (state[j],) + state[i + 1:j] + (state[i],) + state[j + 1:]


def min_swaps(start: State, fa: list[int], n: int, swaps: Swaps) -> int:
    """BFS：第一次生成出合法堆排列时的层数就是最少交换次数。"""
    if is_heap(start, fa, n):
        return 0                            # 初始排列已经是堆，一次都不用交换
    dist = {start: 0}
    queue = deque([start])
    while queue:
        state = queue.popleft()
        for nxt in expand(state, swaps):
            if nxt in dist:
                continue
            dist[nxt] = dist[state] + 1     # BFS 保证首次发现就是最短距离
            if is_heap(nxt, fa, n):
                return dist[nxt]            # 终点是一个集合，命中即答案
            queue.append(nxt)
    return -1                               # 题面保证有解，这里只是兜底


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    fa = [0] + [next(data) for _ in range(n)]     # fa[i] = 结点 i 的父亲，0 表示根
    weights = [next(data) for _ in range(n)]      # weights[i-1] = 结点 i 的点权

    swaps: Swaps = []
    for _ in range(m):
        u, v = next(data), next(data)
        swaps.append((u - 1, v - 1) if u < v else (v - 1, u - 1))

    print(min_swaps(encode(weights, n), fa, n, swaps))


if __name__ == "__main__":
    solve()
