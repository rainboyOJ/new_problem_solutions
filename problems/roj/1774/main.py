#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:53
# update_at: 2026-10-08 01:53

import sys

UNREACHABLE = -1  # 资源值恒 >= 0，所以只要 -1 表示"这个耗时到不了"，不需要更大的负无穷

type Row = list[int]                     # 一个点的 dp 行：下标 = 恰好耗时，值 = 该耗时下的最大资源值
type Son = tuple[Row, Row, Row]          # 一个点的三种腿数状态：(往返, 单腿, 双腿)
type Adj = list[list[tuple[int, int]]]   # adj[u] = [(相邻点, 边耗时), ...]


def attach(src: Son, son: Son, edge: int, base: int, limit: int) -> None:
    """把儿子子树并入 u，src 的三行原地更新；src 与 son 都是 (往返, 单腿, 双腿) 三元组。

    边 (u,v) 走一次的两种接法：v 的"单腿"接成 u 的单腿 / 双腿（路径从 u 继续往 v 的下方走）。
    边 (u,v) 走两次的三种接法："往返"不改变腿数；"双腿"只在 u 还没伸腿时能接（u 自己成了绕路的端点外）。
    """
    old_ret, old_end, old_mid = src[0][:], src[1][:], src[2][:]
    son_ret, son_end, son_mid = son
    # 只踩儿子子树里真正可达的耗时，叶子点只有 1 个可达耗时，能把星形图的合并压成 O(T)
    reach = [s for s in range(limit - edge + 1)
             if son_ret[s] >= 0 or son_end[s] >= 0 or son_mid[s] >= 0]
    ret, end, mid = src
    for k in range(base, limit - edge + 1):   # k：接 v 之前 u 已经花掉的时间
        a0, a1, a2 = old_ret[k], old_end[k], old_mid[k]
        if a0 < 0 and a1 < 0 and a2 < 0:      # 这个耗时在 u 处不可达
            continue
        room = limit - k - edge               # 留给 v 子树的绝对上限
        for s in reach:
            if s > room:                      # reach 递增，后面的 s 更放不下
                break
            j = k + edge + s                  # 边 (u,v) 只走一次
            one = son_end[s]
            if one >= 0:                      # 路径经 (u,v) 进子树，u 这头多伸出一条腿
                cand = a0 + one
                if cand > end[j]:
                    end[j] = cand
                cand = a1 + one
                if cand > mid[j]:
                    mid[j] = cand
            if s + edge > room:               # 边 (u,v) 再走一次放不下
                continue
            j2 = j + edge                     # 往返去 v 子树
            back = son_ret[s]
            if back >= 0:                     # v 内部全是往返，u 的腿数不变
                cand = a0 + back
                if cand > ret[j2]:
                    ret[j2] = cand
                cand = a1 + back
                if cand > end[j2]:
                    end[j2] = cand
                cand = a2 + back
                if cand > mid[j2]:
                    mid[j2] = cand
            both = son_mid[s]
            if both >= 0:                     # v 内部自带整条主路径，u 只是绕过去看一眼
                cand = a0 + both
                if cand > mid[j2]:
                    mid[j2] = cand


def build_dp(n: int, limit: int, weight: Row, fight: Row, adj: Adj, parent: Row, order: list[int]) -> tuple[list[Row], list[Row], list[Row]]:
    """自叶向根做三态树形背包，返回 (往返, 单腿, 双腿) 三张 dp 表。"""
    dp_ret: list[Row] = [[UNREACHABLE] * (limit + 1) for _ in range(n + 1)]
    dp_end: list[Row] = [[UNREACHABLE] * (limit + 1) for _ in range(n + 1)]
    dp_mid: list[Row] = [[UNREACHABLE] * (limit + 1) for _ in range(n + 1)]

    for u in reversed(order):                # 逆序保证轮到 u 时儿子的 dp 行都已算好
        if fight[u] > limit:                  # u 自己打不过；子树由各自的 dp 行负责，答案会另行取到
            continue
        dp_ret[u][fight[u]] = dp_end[u][fight[u]] = dp_mid[u][fight[u]] = weight[u]
        for v, c in adj[u]:
            if v == parent[u]:
                continue
            attach((dp_ret[u], dp_end[u], dp_mid[u]),
                   (dp_ret[v], dp_end[v], dp_mid[v]), c, fight[u], limit)
    return dp_ret, dp_end, dp_mid


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, limit = next(data), next(data)
    weight = [0] + [next(data) for _ in range(n)]   # weight[u]：点 u 的资源值 w_u
    fight = [0] + [next(data) for _ in range(n)]    # fight[u]：点 u 的杀敌耗时 t_u
    adj: Adj = [[] for _ in range(n + 1)]
    edge_count = n - 1                      # 树上边数，题目保证输入恰好这么多条
    for _ in range(edge_count):
        a, b, c = next(data), next(data), next(data)
        adj[a].append((b, c))
        adj[b].append((a, c))

    # 迭代求 dfs 序（父先于子），逆序处理就是自叶向根。
    parent = [0] * (n + 1)
    order: list[int] = []
    stack = [1]
    while stack:
        u = stack.pop()
        order.append(u)
        for v, _ in adj[u]:
            if v != parent[u]:
                parent[v] = u
                stack.append(v)

    ret_rows, end_rows, mid_rows = build_dp(n, limit, weight, fight, adj, parent, order)
    best = max(max(row) for table in (ret_rows, end_rows, mid_rows) for row in table)
    print(max(best, 0))                       # 一个点都进不去时武力值就是 0


if __name__ == "__main__":
    solve()
