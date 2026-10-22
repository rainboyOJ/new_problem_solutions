#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-22 12:26
# update_at: 2026-10-22 12:26
#
# main.py：货车运输。多次询问两点之间「路径最小边权」的最大值（最大瓶颈路）。
# 与 main.cpp 同一算法：Kruskal 建最大生成森林 + 倍增 LCA 维护路径最小边权。
# 图不连通时森林分多个连通块，跨块询问输出 -1。

import sys
from collections import deque

INF = 10**9  # 哨兵：根没有父边、以及题面不会出现的 x == y 询问；z <= 1e5 远小于它

# 树上每个节点存 (父亲, 到父亲的边权, 深度)；点编号 1..n
type Node = tuple[int, int, int]  # (parent, parent_edge_weight, depth)


def find(parent: list[int], x: int) -> int:
    """找 x 所在集合的根，顺路把路径上的点挂到根上（迭代压缩）。"""
    root = x
    while parent[root] != root:
        root = parent[root]
    while parent[x] != root:
        parent[x], x = root, parent[x]
    return root


def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 只靠路径压缩：单次操作摊还 O(log n)，本题 n <= 1e4 已经足够
    parent = list(range(n + 1))
    edges: list[tuple[int, int, int]] = []
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        edges.append((u, v, w))

    # ---- Kruskal：按边权从大到小建最大生成森林，树边存成 children 列表 ----
    children: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for u, v, w in sorted(edges, key=lambda e: e[2], reverse=True):
        ru, rv = find(parent, u), find(parent, v)
        if ru != rv:
            parent[ru] = rv
            children[u].append((v, w))
            children[v].append((u, w))

    # ---- 每个连通块 BFS，求父亲、到父亲的边权、深度、连通块编号 ----
    nodes: list[Node] = [(-1, -1, -1)] * (n + 1)  # 根为 (0, INF, 1)
    component = [0] * (n + 1)  # component[x]：x 所在连通块编号
    cid = 0
    for start in range(1, n + 1):
        if component[start]:
            continue
        cid += 1
        nodes[start] = (0, INF, 1)
        component[start] = cid
        que = deque([start])
        while que:
            u = que.popleft()
            pu, _, du = nodes[u]
            for v, w in children[u]:
                if v == pu:  # 不走回父节点
                    continue
                nodes[v] = (u, w, du + 1)
                component[v] = cid
                que.append(v)

    # ---- 倍增表：up[j][x] 向上跳 2^j 条边的祖先，mn[j][x] 该段路径最小边权 ----
    LOG = max(1, (n).bit_length())  # 2^(LOG-1) >= n，覆盖最大树深
    up = [[-1] * (n + 1) for _ in range(LOG)]  # 用 -1 表示「根之上」的虚拟点
    mn = [[INF] * (n + 1) for _ in range(LOG)]
    for x in range(1, n + 1):
        up[0][x], mn[0][x] = nodes[x][0], nodes[x][1]

    for j in range(1, LOG):  # 递推：先跳 2^(j-1) 再跳 2^(j-1)
        upj, upj1 = up[j], up[j - 1]
        mnj, mnj1 = mn[j], mn[j - 1]
        for x in range(1, n + 1):
            mid = upj1[x]
            if mid < 0:
                upj[x], mnj[x] = -1, INF
            else:
                upj[x] = upj1[mid]
                mnj[x] = min(mnj1[x], mnj1[mid])

    # ---- 查询：深点先跳齐，再一起跳到 LCA，沿途取最小边权 ----
    def query(x: int, y: int) -> int:
        if component[x] != component[y]:
            return -1  # 不在同一连通块，货车无法到达
        answer = INF
        px, py = nodes[x], nodes[y]
        if px[2] < py[2]:  # 让 x 是更深的那个
            x, y = y, x
            px, py = py, px
        # 第一步：把 x 跳到与 y 同深度
        diff = px[2] - py[2]
        for j in range(LOG - 1, -1, -1):
            if diff >> j & 1:
                answer = min(answer, mn[j][x])
                x = up[j][x]
        if x == y:
            # y 本来就是 x 的祖先，刚才跳过的段就是全部路径
            return answer
        # 第二步：两个点一起向上跳到 LCA 的儿子
        for j in range(LOG - 1, -1, -1):
            if up[j][x] != up[j][y]:
                answer = min(answer, mn[j][x], mn[j][y])
                x, y = up[j][x], up[j][y]
        # 最后各自跳一条父边到 LCA
        answer = min(answer, mn[0][x], mn[0][y])
        return answer

    out = []
    q = next(data)
    for _ in range(q):
        x, y = next(data), next(data)
        out.append(str(query(x, y)))
    print("\n".join(out))


if __name__ == "__main__":
    main()
