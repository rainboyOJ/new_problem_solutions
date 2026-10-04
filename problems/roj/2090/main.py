#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 08:30
# update_at: 2026-10-01 09:46

import sys
from collections import deque

INF = 1 << 30  # 连接与起止电脑的容量：线路不会坏，c1/c2 不许坏


def build_net(n: int, adj: list[list[int]], broken: set[int], safe: set[int]) -> list[list[list[int]]]:
    """拆点建流网络：broken 里的电脑容量 0（当作已坏），safe 里容量 INF（不许坏），其余容量 1。"""
    net: list[list[list[int]]] = [[] for _ in range(2 * n + 2)]  # 点 v 的入点 2v、出点 2v+1

    def add_arc(u: int, v: int, cap: int) -> None:
        """加一对正反弧：反向弧初始容量 0，供增广路回退流量。"""
        net[u].append([v, cap, len(net[v])])
        net[v].append([u, 0, len(net[u]) - 1])

    for v in range(1, n + 1):
        # 点内部弧 v入->v出：容量 1 表示"拆掉这台电脑"的代价
        cap = 0 if v in broken else INF if v in safe else 1
        add_arc(2 * v, 2 * v + 1, cap)
    for u in range(1, n + 1):
        for v in adj[u]:
            if u < v:  # 每条无向连接拆成两个方向，容量 INF：坏的是电脑不是线
                add_arc(2 * u + 1, 2 * v, INF)
                add_arc(2 * v + 1, 2 * u, INF)
    return net


def max_flow(net: list[list[list[int]]], s: int, t: int) -> int:
    """Dinic 求 s 到 t 的最大流；按最大流最小割定理，它等于拆点网络的最小点割容量。"""
    flow = 0
    while True:
        level = [-1] * len(net)  # 分层图：只保留能层层推向 t 的弧
        level[s] = 0
        queue = deque([s])
        while queue:
            u = queue.popleft()
            for v, cap, _ in net[u]:
                if cap and level[v] < 0:
                    level[v] = level[u] + 1
                    queue.append(v)
        if level[t] < 0:
            return flow
        cur = [0] * len(net)

        def dfs(u: int) -> int:
            """在分层图上从 u 尽量往 t 推流，返回本条增广路推出的量。"""
            if u == t:
                return 1
            while cur[u] < len(net[u]):
                v, cap, rev = net[u][cur[u]]
                if cap and level[v] == level[u] + 1:
                    pushed = dfs(v)
                    if pushed:
                        net[u][cur[u]][1] -= pushed
                        net[v][rev][1] += pushed
                        return pushed
                cur[u] += 1
            return 0

        while (pushed := dfs(s)):  # 一层内榨干所有增广路再重新分层
            flow += pushed


def lex_min_cut(n: int, adj: list[list[int]], c1: int, c2: int) -> list[int]:
    """字典序最小的最小点割：先求最小割大小 k，再按编号从小到大逐点判定能否入选。"""
    safe: set[int] = {c1, c2}  # 起止电脑永远不许坏
    k = max_flow(build_net(n, adj, set(), safe), 2 * c1, 2 * c2)

    cut: list[int] = []
    for v in range(1, n + 1):
        if v in safe:
            continue  # 起止点与已排除点不再试探
        # 试探 v 入选：已选点当作已坏，已排除点设为不可坏；
        # 若剩余网络的最小割恰好 = 还差的点数 k-|cut|-1，则存在"含 v"的最小割
        rest = k - len(cut) - 1
        flow = max_flow(build_net(n, adj, set(cut) | {v}, safe), 2 * c1, 2 * c2)
        if flow == rest:  # 必有 flow >= rest，取等即说明含 v 的最小割存在
            cut.append(v)  # 收下 v，让答案这一位尽可能小
        else:
            safe.add(v)  # 含 v 达不到最小规模：任何最小割都不含 v
    return cut


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, c1, c2 = next(data), next(data), next(data), next(data)

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(m):
        a, b = next(data), next(data)
        adj[a].append(b)  # 连接双向
        adj[b].append(a)

    cut = lex_min_cut(n, adj, c1, c2)
    print(len(cut))
    print(' '.join(map(str, cut)))


if __name__ == "__main__":
    solve()
