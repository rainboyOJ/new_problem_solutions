#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:56
# update_at: 2026-09-30 15:56

import sys


def count_disasters(adj: list[set[int]], n: int) -> int:
    """Tarjan 求割点数量：根看 DFS 子树数 ≥2，其余点看是否有孩子 low ≥ dfn。"""
    dfn = [0] * (n + 1)   # DFS 编号，0 表示尚未访问
    low = [0] * (n + 1)   # 子树内能到达的最小 DFS 编号
    is_cut = [False] * (n + 1)
    clock = 0             # DFS 时间戳，编号从 1 开始，0 留给"未访问"

    def dfs(u: int, parent: int) -> None:
        nonlocal clock
        clock += 1
        dfn[u] = low[u] = clock
        children = 0
        for v in adj[u]:
            if v == parent:          # 无向图唯一的父边不算回边
                continue
            if dfn[v]:
                low[u] = min(low[u], dfn[v])   # 回边：v 是祖先
            else:
                children += 1
                dfs(v, u)
                low[u] = min(low[u], low[v])
                # 子树 v 连不回 u 的祖先：删掉 u，v 那部分就断开了
                if parent and low[v] >= dfn[u]:
                    is_cut[u] = True
        if not parent and children > 1:        # 根断开后至少剩两棵互不相通的子树
            is_cut[u] = True

    for u in range(1, n + 1):        # 图保证连通；兜底处理万一的非连通块
        if not dfn[u]:
            dfs(u, 0)
    return sum(is_cut)


def solve() -> None:
    readline = sys.stdin.buffer.readline
    out: list[str] = []

    while True:
        line = readline()
        if not line:
            break
        n = int(line)
        if n == 0:                   # 最后一个块只有单独一个 0
            break

        adj: list[set[int]] = [set() for _ in range(n + 1)]
        while True:
            row = list(map(int, readline().split()))
            if row[0] == 0:          # 单独一行 0 结束本块
                break
            u = row[0]
            for v in row[1:]:        # 无向边：一条边至少在某一行出现，双向登记
                adj[u].add(v)
                adj[v].add(u)

        out.append(str(count_disasters(adj, n)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
