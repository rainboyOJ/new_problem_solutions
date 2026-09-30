#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 07:30
# update_at: 2026-10-01 07:30

import sys
from collections import deque

INF = 10**18  # 增广时的“无穷大”上界


def dinic(adj: list[list[int]], to: list[int], caps: list[int], n: int) -> int:
    """当前容量 caps 下，节点 1 到节点 n 的最大流（Dinic 算法）。"""
    flow = 0
    s, t = 1, n
    while True:
        level = [-1] * (n + 1)  # BFS 分层
        level[s] = 0
        dq = deque([s])
        while dq:
            u = dq.popleft()
            for eid in adj[u]:
                v = to[eid]
                if caps[eid] > 0 and level[v] < 0:
                    level[v] = level[u] + 1
                    dq.append(v)
        if level[t] < 0:  # 汇点不可达，当前流已是最大流
            return flow

        it = [0] * (n + 1)  # 每个节点的弧指针：只扫一遍被拒绝的弧

        def push(u: int, f: int) -> int:
            """沿 level 严格递增的路径把流量 f 尽量送到汇点，返回实际送出量。"""
            if u == t:
                return f
            while it[u] < len(adj[u]):
                eid = adj[u][it[u]]
                v = to[eid]
                if caps[eid] > 0 and level[v] == level[u] + 1:
                    d = push(v, min(f, caps[eid]))
                    if d:
                        caps[eid] -= d
                        caps[eid ^ 1] += d
                        return d
                it[u] += 1
            return 0

        while True:
            d = push(s, INF)
            if not d:
                break
            flow += d


def make_caps(removed: list[bool], W: list[int], m: int) -> list[int]:
    """按 removed 状态重建容量数组：已移除的边容量为 0，其余为修改容量。"""
    caps = [0] * (2 * m)
    for i in range(m):
        if not removed[i]:
            caps[2 * i] = W[i]
    return caps


def extract_cut_edges(adj: list[list[int]], to: list[int], n: int, m: int, W: list[int]) -> tuple[int, list[int]]:
    """贪心提取最小割：返回 (修改图最大流, 按输入顺序排列的割边行号)。

    逐条删除边并重跑最大流，若最大流恰好减少该边的修改容量 w_e，说明任何最大流
    都无法绕开它，它属于某个最小割 → 保留删除；否则恢复。修改容量已“先压损失、
    再压边数”，故删掉的边集就是“总代价最小、边数最少”的最优割。
    """
    removed = [False] * m  # 已确认属于最小割的边
    flow0 = dinic(adj, to, make_caps(removed, W, m), n)
    flow = flow0
    ans: list[int] = []
    for i in range(m):
        removed[i] = True
        nxt = dinic(adj, to, make_caps(removed, W, m), n)
        drop_full = flow - nxt == W[i]  # 恰好损失自己的容量：e 属于最小割
        if drop_full:
            ans.append(i + 1)  # 卡车行号从 1 开始
            flow = nxt
        else:
            removed[i] = False
    return flow0, ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)  # 仓库数 n、卡车数 m（真实数据为 n 在前）
    edges = [(next(data), next(data), next(data)) for _ in range(m)]  # (起点, 终点, 停运损失)

    K = m + 1  # 修改容量的放大系数：任何割的边数都小于 K
    W = [c * K + 1 for _, _, c in edges]  # 修改容量：损失 c 的边变成 c*K+1

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    to = [0] * (2 * m)
    for i, (u, v, _) in enumerate(edges):
        fwd, rev = 2 * i, 2 * i + 1
        to[fwd], to[rev] = v, u
        adj[u].append(fwd)
        adj[v].append(rev)

    flow0, ans = extract_cut_edges(adj, to, n, m, W)
    cost, count = flow0 // K, len(ans)  # 商是最小损失，余数是所选边数
    out = [f"{cost} {count}"] + [str(i) for i in ans]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
