#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:04
# update_at: 2026-09-30 18:19

import sys


def build_chains(n: int, adj: list[list[int]], root: int = 1) -> tuple[list[int], list[int], list[int]]:
    """预处理树：返回父表 parent、深度表 depth 和重链顶表 head，供 O(log n) 求 LCA。"""
    parent = [0] * (n + 1)
    depth = [0] * (n + 1)
    order = [root]
    for u in order:                                # 列表边长边迭代，等价于先根遍历整棵树
        for v in adj[u]:
            if v != parent[u]:                     # 邻居里只有父点需要避开
                parent[v] = u
                depth[v] = depth[u] + 1
                order.append(v)

    size = [1] * (n + 1)
    for u in reversed(order):                      # 反向先根序 = 后根序，子树先于父点结算
        size[parent[u]] += size[u]                 # 根的 parent 是 0，下标 0 不会被查询

    head = [0] * (n + 1)
    heavy = [0] * (n + 1)
    for u in order:                                # 正向先根序，父点的 heavy 此时已就绪
        p = parent[u]
        head[u] = head[p] if heavy[p] == u else u  # 是父点的重儿子就共用链顶，否则自成链顶
        for v in adj[u]:
            if v != p and (heavy[u] == 0 or size[v] > size[heavy[u]]):
                heavy[u] = v                       # 最大子树即重儿子，轻边每次跨越都让子树至少减半
    return parent, depth, head


def query_lca(u: int, v: int, depth: list[int], parent: list[int], head: list[int]) -> int:
    """重链跳跃求 LCA：每次把链顶更深的那条链整体上移到父链，同链时浅者即答案。"""
    while head[u] != head[v]:
        if depth[head[u]] < depth[head[v]]:
            u, v = v, u
        u = parent[head[u]]
    return u if depth[u] < depth[v] else v


def meeting(a: int, b: int, c: int, depth: list[int], parent: list[int], head: list[int]) -> tuple[int, int]:
    """一次聚会：返回费用最小的聚会点 P 与最小总费用 C，三对 LCA 一次问齐。"""
    ab, bc, ca = (query_lca(u, v, depth, parent, head) for u, v in ((a, b), (b, c), (c, a)))

    # 聚会点 = 三条两两路径的唯一公共点 = 三对 LCA 中最深的那个（同深度必为同点）
    p = ab
    if depth[bc] > depth[p]:
        p = bc
    if depth[ca] > depth[p]:
        p = ca

    # 最小费用 = 两两距离和 ÷ 2 = 三点深度和 − 三个 LCA 深度和
    return p, depth[a] + depth[b] + depth[c] - depth[ab] - depth[bc] - depth[ca]


def solve() -> None:
    data = (int(t) for line in sys.stdin.buffer for t in line.split())  # 逐行惰性读入，5×10^5 行不整份驻留内存
    n, m = next(data), next(data)

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b = next(data), next(data)
        adj[a].append(b)
        adj[b].append(a)

    parent, depth, head = build_chains(n, adj)

    out: list[str] = []
    for _ in range(m):
        a, b, c = next(data), next(data), next(data)
        out.append("%d %d" % meeting(a, b, c, depth, parent, head))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
