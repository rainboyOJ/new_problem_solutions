#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 00:20
# update_at: 2026-10-02 00:20

import sys


def lca(u: int, v: int, depth: list[int], up: list[list[int]]) -> int:
    """返回 u,v 的最近公共祖先（二进制提升表 up）。"""
    if depth[u] < depth[v]:  # 统一让 u 更深
        u, v = v, u
    diff = depth[u] - depth[v]
    for k in range(len(up)):
        if diff >> k & 1:  # u 上提 diff 的每个二进制位
            u = up[k][u]
    if u == v:
        return u
    for k in range(len(up) - 1, -1, -1):  # 从高位跳，落到最近公共祖先的下一层
        if up[k][u] != up[k][v]:
            u, v = up[k][u], up[k][v]
    return up[0][u]


def bfs_order(adj: list[list[int]]) -> tuple[list[int], list[int], list[int]]:
    """从 1 号点 BFS，返回 (访问顺序, 父节点, 深度)；order 边遍历边增长，等价于队列。"""
    size = len(adj)
    parent = [0] * size  # 0 号点是根的哨兵父节点
    depth = [0] * size
    order = [1]
    for u in order:
        for v in adj[u]:
            if v != parent[u]:
                parent[v] = u
                depth[v] = depth[u] + 1
                order.append(v)
    return order, parent, depth


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b = next(data), next(data)
        adj[a].append(b)
        adj[b].append(a)

    order, parent, depth = bfs_order(adj)

    up = [parent]  # up[k][v]：v 向上跳 2^k 步到的祖先，0 号点是哨兵
    for _ in range(max(1, (n - 1).bit_length())):
        prev_up = up[-1]
        up.append([prev_up[x] for x in prev_up])

    qx = [0] * m
    qy = [0] * m
    qz = [0] * m
    for i in range(m):
        qx[i] = next(data)
        qy[i] = next(data)
        qz[i] = next(data)

    kinds = sorted(set(qz))                     # 离散化：叶子编号 -> 物品种类
    rank = {z: i for i, z in enumerate(kinds)}  # 物品种类 -> 叶子编号
    # 叶子数 K 必须同时 >= 种类数（装下所有差分点）和 n-1 的位长（merge 时两树区间一致）
    K = max(len(kinds), (n - 1).bit_length())

    # 动态开点权值线段树（数组版），0 号点是空树哨兵；闭包访问比全局快
    # mx[v]：v 子树内最大的单类计数（不是区间和！）；best[v]：取到该最大值的叶子编号
    left = [0]
    right = [0]
    mx = [0]
    best = [0]

    def pull(node: int) -> None:
        """由左右孩子重算 node 的 (mx, best)；并列取左孩子 = 编号更小的种类。"""
        lc, rc = left[node], right[node]
        if mx[lc] >= mx[rc]:
            mx[node] = mx[lc]
            best[node] = best[lc]
        else:
            mx[node] = mx[rc]
            best[node] = best[rc]

    def insert(root: int, pos: int, delta: int) -> int:
        """在 root 的树上给叶子 pos 加 delta（差分点），缺路径就动态开点。"""
        if not root:
            left.append(0)
            right.append(0)
            mx.append(0)
            best.append(0)
            root = len(mx) - 1
        cur, l, r = root, 0, K - 1
        path = [cur]  # 自顶向下记录路径，最后统一回推 (mx, best)
        while l < r:
            mid = (l + r) >> 1
            if pos <= mid:
                nxt = left[cur]
                if not nxt:
                    left.append(0)
                    right.append(0)
                    mx.append(0)
                    best.append(0)
                    nxt = len(mx) - 1
                    left[cur] = nxt
                r = mid
            else:
                nxt = right[cur]
                if not nxt:
                    left.append(0)
                    right.append(0)
                    mx.append(0)
                    best.append(0)
                    nxt = len(mx) - 1
                    right[cur] = nxt
                l = mid + 1
            cur = nxt
            path.append(cur)
        mx[cur] += delta  # 到达叶子：叶子上的计数本身就是它的 mx
        best[cur] = l
        for node in reversed(path[:-1]):  # 只回推内部节点，叶子的 mx 刚刚手工赋值
            pull(node)
        return root

    def merge(a: int, b: int) -> int:
        """把线段树 b 破坏式并入 a，返回新根；两树同区间，叶子性一致。"""
        if not a or not b:
            return a | b
        if not left[a] and not right[a]:  # a 是叶子 <=> 区间长 1，b 同区间也必是叶子
            mx[a] += mx[b]  # 叶子计数相加，种类不变
            return a
        left[a] = merge(left[a], left[b])
        right[a] = merge(right[a], right[b])
        pull(a)
        return a

    def mode_kind(root: int) -> int:
        """返回树中计数最大的物品种类；并列取编号最小，空树返回 0。"""
        return kinds[best[root]] if mx[root] > 0 else 0

    # 树上差分：路径 (x,y) 拆成 x+1、y+1、lca-1、lca父-1
    roots = [0] * (n + 1)
    for i in range(m):
        x, y, kind = qx[i], qy[i], rank[qz[i]]
        l = lca(x, y, depth, up)
        roots[x] = insert(roots[x], kind, 1)
        roots[y] = insert(roots[y], kind, 1)
        roots[l] = insert(roots[l], kind, -1)
        if parent[l]:
            roots[parent[l]] = insert(roots[parent[l]], kind, -1)

    # 逆 BFS 序：u 的树已含全部子树差分时先取答案，再并入父节点
    ans = [0] * (n + 1)
    for u in reversed(order):
        ans[u] = mode_kind(roots[u])
        if parent[u]:
            roots[parent[u]] = merge(roots[parent[u]], roots[u])

    sys.stdout.write('\n'.join(map(str, ans[1:])) + '\n')


if __name__ == "__main__":
    solve()
