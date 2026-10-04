#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 03:07
# update_at: 2026-10-02 03:07

import sys

NO_ROUND_TRIP = 'Round trip does not exist.'


def euler_tour(start: int, adj: dict[int, list[tuple[int, int]]]) -> list[int]:
    """从 start 出发走遍每条街道且只走一次再回到 start，返回街道编号序列。

    邻接表按街道编号升序：每一步都贪心走"当前能用、编号最小的街道"，走不动时再回溯，
    得到的回路字典序最小。栈里存 (路口, 进入该路口所走的街道)，回溯时收集到的编号是
    逆序的，最后整体翻转一次。
    """
    used: set[int] = set()      # 街道编号是任意整数（不一定 1..n），用集合判断是否走过
    pos: dict[int, int] = {}    # 各路口扫描到邻接表的下标，跳过已用街道的代价才能摊还成 O(1)
    route: list[int] = []
    stack = [(start, 0)]        # 哨兵 0：出发点没有"进入街道"
    while stack:
        u, entered = stack[-1]
        edges = adj[u]
        i = pos.get(u, 0)
        while i < len(edges) and edges[i][0] in used:   # edges[i] = (街道编号, 另一端路口)
            i += 1              # 同一路口可能被多次经过，被跳过的街道下标只前进不后退
        if i < len(edges):
            street, v = edges[i]
            pos[u] = i + 1      # 这条街道已经被这一步占用，下次直接从下一条看起
            used.add(street)
            stack.append((v, street))
        else:
            pos[u] = i
            stack.pop()
            if entered:
                route.append(entered)
    route.reverse()
    return route


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while True:
        edges: list[tuple[int, int, int]] = []
        while True:
            x, y = next(data), next(data)
            if x == 0 and y == 0:
                break
            edges.append((x, y, next(data)))
        if not edges:
            break               # 空用例的 0 0：整份输入结束

        start = min(edges[0][0], edges[0][1])   # 题面：第一条街道两端较小编号的路口是家

        adj: dict[int, list[tuple[int, int]]] = {}
        for x, y, street in edges:
            adj.setdefault(x, []).append((street, y))
            adj.setdefault(y, []).append((street, x))
        for neighbours in adj.values():
            neighbours.sort()   # 按街道编号升序，Hierholzer 才取得到字典序最小的回路

        seen = {start}
        frontier = [start]
        while frontier:
            for _, v in adj[frontier.pop()]:
                if v not in seen:
                    seen.add(v)
                    frontier.append(v)

        all_degrees_even = all(len(neighbours) % 2 == 0 for neighbours in adj.values())
        connected = len(seen) == len(adj)   # 所有路口都在出发点的连通块里

        out.append(
            ' '.join(map(str, euler_tour(start, adj)))
            if all_degrees_even and connected
            else NO_ROUND_TRIP
        )

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
