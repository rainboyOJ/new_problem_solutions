#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:15
# update_at: 2026-09-30 18:15

import sys

INF = 10**9


def build_tree_layout(n: int, adj: list[list[int]], root: int = 1) -> tuple[list[int], list[int], list[int], list[int]]:
    """以非递归遍历剖分树链，返回父节点、深度、重链顶与 DFS 序映射。"""
    parent = [0] * (n + 1)
    depth = [0] * (n + 1)
    heavy = [0] * (n + 1)
    size = [1] * (n + 1)

    order: list[int] = []
    stack = [root]
    depth[root] = 1
    while stack:
        u = stack.pop()
        order.append(u)
        for v in adj[u]:
            if v != parent[u]:
                parent[v] = u
                depth[v] = depth[u] + 1
                stack.append(v)

    # 倒序回溯计算子树大小及重儿子
    for u in reversed(order):
        heavy_child, max_s = 0, 0
        for v in adj[u]:
            if v != parent[u]:
                size[u] += size[v]
                if size[v] > max_s:
                    max_s = size[v]
                    heavy_child = v
        heavy[u] = heavy_child

    # 二次遍历确定重链顶与 DFS 序
    top = [0] * (n + 1)
    dfn = [0] * (n + 1)
    timer = 0
    stack = [(root, root)]
    while stack:
        u, chain_top = stack.pop()
        timer += 1
        dfn[u] = timer
        top[u] = chain_top

        # 轻儿子先压栈，重儿子后压栈保证先访问重儿子
        for v in adj[u]:
            if v != parent[u] and v != heavy[u]:
                stack.append((v, v))
        if heavy[u]:
            stack.append((heavy[u], chain_top))

    return parent, depth, top, dfn


class SegmentTree:
    """维护区间和与区间最大值的线段树。"""

    def __init__(self, n: int, initial_weights: list[int]) -> None:
        self.size = 1
        while self.size <= n + 1:
            self.size <<= 1
        self.tree_max = [-INF] * (2 * self.size)
        self.tree_sum = [0] * (2 * self.size)
        for i, w in enumerate(initial_weights, 1):
            pos = self.size + i
            self.tree_max[pos] = w
            self.tree_sum[pos] = w
        for i in range(self.size - 1, 0, -1):
            left, right = i << 1, (i << 1) | 1
            self.tree_max[i] = max(self.tree_max[left], self.tree_max[right])
            self.tree_sum[i] = self.tree_sum[left] + self.tree_sum[right]

    def update(self, pos: int, val: int) -> None:
        """单点修改：把位置 pos 的值赋为 val。"""
        idx = self.size + pos
        self.tree_max[idx] = val
        self.tree_sum[idx] = val
        idx >>= 1
        while idx:
            left, right = idx << 1, (idx << 1) | 1
            self.tree_max[idx] = max(self.tree_max[left], self.tree_max[right])
            self.tree_sum[idx] = self.tree_sum[left] + self.tree_sum[right]
            idx >>= 1

    def query_max(self, left: int, right: int) -> int:
        """区间求最大值 [left, right]。"""
        res = -INF
        left += self.size
        right += self.size + 1
        while left < right:
            if left & 1:
                res = max(res, self.tree_max[left])
                left += 1
            if right & 1:
                right -= 1
                res = max(res, self.tree_max[right])
            left >>= 1
            right >>= 1
        return res

    def query_sum(self, left: int, right: int) -> int:
        """区间求和 [left, right]。"""
        res = 0
        left += self.size
        right += self.size + 1
        while left < right:
            if left & 1:
                res += self.tree_sum[left]
                left += 1
            if right & 1:
                right -= 1
                res += self.tree_sum[right]
            left >>= 1
            right >>= 1
        return res


def path_max(u: int, v: int, parent: list[int], depth: list[int], top: list[int], dfn: list[int], seg: SegmentTree) -> int:
    """求路径 u 到 v 上的节点权值最大值。"""
    res = -INF
    while top[u] != top[v]:
        if depth[top[u]] < depth[top[v]]:
            u, v = v, u
        res = max(res, seg.query_max(dfn[top[u]], dfn[u]))
        u = parent[top[u]]
    if depth[u] > depth[v]:
        u, v = v, u
    res = max(res, seg.query_max(dfn[u], dfn[v]))
    return res


def path_sum(u: int, v: int, parent: list[int], depth: list[int], top: list[int], dfn: list[int], seg: SegmentTree) -> int:
    """求路径 u 到 v 上的节点权值和。"""
    res = 0
    while top[u] != top[v]:
        if depth[top[u]] < depth[top[v]]:
            u, v = v, u
        res += seg.query_sum(dfn[top[u]], dfn[u])
        u = parent[top[u]]
    if depth[u] > depth[v]:
        u, v = v, u
    res += seg.query_sum(dfn[u], dfn[v])
    return res


def solve() -> None:
    raw = sys.stdin.buffer.read().split()
    if not raw:
        return
    it = iter(raw)

    n = int(next(it))
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u = int(next(it))
        v = int(next(it))
        adj[u].append(v)
        adj[v].append(u)

    raw_weights = [0] + [int(next(it)) for _ in range(n)]

    parent, depth, top, dfn = build_tree_layout(n, adj)

    # 按照 dfn 序重排初始权值
    seg_init = [0] * n
    for u in range(1, n + 1):
        seg_init[dfn[u] - 1] = raw_weights[u]

    seg = SegmentTree(n, seg_init)

    q = int(next(it))
    out: list[str] = []

    for _ in range(q):
        op = next(it).decode()
        u = int(next(it))
        v_or_val = int(next(it))
        if op == "CHANGE":
            seg.update(dfn[u], v_or_val)
        elif op == "QMAX":
            ans = path_max(u, v_or_val, parent, depth, top, dfn, seg)
            out.append(str(ans))
        else:
            ans = path_sum(u, v_or_val, parent, depth, top, dfn, seg)
            out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
