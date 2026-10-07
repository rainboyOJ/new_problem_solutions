#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 22:28
# update_at: 2026-10-07 22:28

import sys
from collections.abc import Iterator

NONE = -1  # 线段树查询的哨兵：该区间里没有任何安全系数达标的城市

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Adj = list[list[tuple[int, int]]]  # 邻接表：点 -> [(邻点, 边权)]
type Tree = list[int]                   # 迭代式线段树，下标 1 起，存区间最大安全系数
type Hld = tuple[list[int], list[int], list[int], list[int], list[int]]
# Hld = (par, dep, head, pos, node_at)：父结点 / 深度 / 重链链头 / 剖分下标 / 下标对应点
type Seg = tuple[Tree, int]             # (线段树, 叶子偏移 size)


def tree_bfs(adj: Adj, root: int) -> tuple[list[int], list[int], list[int], list[int]]:
    """从 root 做 BFS，返回（访问序、父结点、深度、带权距离）。"""
    n = len(adj) - 1
    par = [0] * (n + 1)
    dep = [0] * (n + 1)
    dist = [0] * (n + 1)
    order = [root]
    for u in order:  # 边遍历边追加：BFS 序里父结点一定先于子结点出现
        for v, w in adj[u]:
            if v != par[u]:
                par[v] = u
                dep[v] = dep[u] + 1
                dist[v] = dist[u] + w
                order.append(v)
    return order, par, dep, dist


def farthest_node(adj: Adj, start: int) -> tuple[int, list[int]]:
    """返回离 start 最远的点编号，以及各点到 start 的距离。"""
    _order, _par, _dep, dist = tree_bfs(adj, start)
    best = start
    for i in range(1, len(dist)):
        if dist[i] > dist[best]:
            best = i
    return best, dist


def safety_values(adj: Adj, a: int, b: int, c: int) -> list[int]:
    """每个城市的安全系数 S_i = ((d_i + a) * b) mod c。

    d_i 是「到最远边境城市的距离」。树里任意点的最远点必是直径端点，
    而直径两端都是叶子（度 1），也就是边境城市，所以两遍 BFS 定出直径两端 A、B 后
    d_i = max(dist(i, A), dist(i, B))；n = 1 时没有边境城市，两个距离都是 0。
    """
    end_a, _ = farthest_node(adj, 1)            # 任取一点求最远点 A
    end_b, dist_a = farthest_node(adj, end_a)   # A 的最远点就是直径另一端 B
    _, dist_b = farthest_node(adj, end_b)
    return [0] + [((max(dist_a[i], dist_b[i]) + a) * b) % c for i in range(1, len(adj))]


def heavy_light(adj: Adj) -> Hld:
    """树链剖分：重链在 pos 上占一段连续下标，且下标随深度递增。"""
    n = len(adj) - 1
    order, par, dep, _dist = tree_bfs(adj, 1)

    # 子树大小与重儿子：逆 BFS 序自底向上合并
    sub = [1] * (n + 1)
    heavy = [0] * (n + 1)
    for u in reversed(order[1:]):
        p = par[u]
        sub[p] += sub[u]
        if heavy[p] == 0 or sub[u] > sub[heavy[p]]:
            heavy[p] = u

    # 每个链头带着它的重链一路往下占下标
    head = [0] * (n + 1)
    pos = [0] * (n + 1)
    node_at = [0] * n
    cur = 0
    for u in order:
        if u == 1 or heavy[par[u]] != u:  # u 是链头（根，或不是父结点的重儿子）
            v = u
            while v:
                head[v] = u
                pos[v] = cur
                node_at[cur] = v
                cur += 1
                v = heavy[v]
    return par, dep, head, pos, node_at


def lca(u: int, v: int, hld: Hld) -> int:
    """最近公共祖先：谁所在重链的链头更深就先跳谁。"""
    par, dep, head = hld[0], hld[1], hld[2]
    while head[u] != head[v]:
        if dep[head[u]] < dep[head[v]]:
            u, v = v, u
        u = par[head[u]]
    return u if dep[u] < dep[v] else v


def build_seg(values: list[int]) -> Seg:
    """按剖分下标顺序建迭代式线段树，返回 (树, 叶子偏移)。"""
    size = 1
    while size < len(values):
        size <<= 1
    tree = [0] * (2 * size)
    tree[size:size + len(values)] = values
    for i in range(size - 1, 0, -1):
        tree[i] = max(tree[2 * i], tree[2 * i + 1])
    return tree, size


def seg_nodes(lo: int, hi: int, size: int) -> tuple[list[int], list[int]]:
    """把区间 [lo, hi] 拆成线段树的标准结点，返回（左半从左到右、右半从右到左）。

    左右两半拼起来是 [左半] + 反转(右半)，即从左到右的覆盖顺序。
    """
    lo += size
    hi += size + 1
    left: list[int] = []
    right: list[int] = []
    while lo < hi:
        if lo & 1:
            left.append(lo)
            lo += 1
        if hi & 1:
            hi -= 1
            right.append(hi)
        lo >>= 1
        hi >>= 1
    return left, right


def rightmost(tree: Tree, size: int, lo: int, hi: int, q: int) -> int:
    """[lo, hi] 内下标最大且值 >= q 的叶子位置，没有则 NONE。"""
    left, right = seg_nodes(lo, hi, size)
    for nd in right + left[::-1]:  # 从右往左扫标准结点，首个含解的结点里再往右沉
        if tree[nd] >= q:
            while nd < size:
                nd = 2 * nd + 1 if tree[2 * nd + 1] >= q else 2 * nd
            return nd - size
    return NONE


def leftmost(tree: Tree, size: int, lo: int, hi: int, q: int) -> int:
    """[lo, hi] 内下标最小且值 >= q 的叶子位置，没有则 NONE。"""
    left, right = seg_nodes(lo, hi, size)
    for nd in left + right[::-1]:  # 从左往右扫标准结点，首个含解的结点里再往左沉
        if tree[nd] >= q:
            while nd < size:
                nd = 2 * nd if tree[2 * nd] >= q else 2 * nd + 1
            return nd - size
    return NONE


def first_on_path(x: int, y: int, q: int, hld: Hld, seg: Seg) -> int:
    """x -> y 路径上离 x 最近且安全系数 >= q 的城市编号，不存在返回 -1。

    路径以 lca 为界分两半：x 到 lca 这一半要从 x 往上走，取最靠右（下标最大）的解；
    只有它整段无解时才看 lca 到 y 那一半，此时离 x 最近等于离 lca 最近，
    于是把各段按从深到浅收好、倒序扫描，段内取最靠左的解。
    """
    par, dep, head, pos, node_at = hld
    tree, size = seg
    top = lca(x, y, hld)

    u = x
    while head[u] != head[top]:
        idx = rightmost(tree, size, pos[head[u]], pos[u], q)
        if idx != NONE:
            return node_at[idx]
        u = par[head[u]]
    idx = rightmost(tree, size, pos[top], pos[u], q)
    if idx != NONE:
        return node_at[idx]

    down: list[tuple[int, int]] = []
    v = y
    while head[v] != head[top]:
        down.append((pos[head[v]], pos[v]))
        v = par[head[v]]
    if pos[v] > pos[top]:  # 同一条重链上的最后一小段，去掉 lca 自己
        down.append((pos[top] + 1, pos[v]))
    for lo, hi in reversed(down):
        idx = leftmost(tree, size, lo, hi, q)
        if idx != NONE:
            return node_at[idx]
    return -1


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a, b, c = next(data), next(data), next(data)

    adj: Adj = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v, w = next(data), next(data), next(data)
        adj[u].append((v, w))
        adj[v].append((u, w))

    safety = safety_values(adj, a, b, c)
    hld = heavy_light(adj)
    node_at = hld[4]
    seg = build_seg([safety[node_at[i]] for i in range(n)])

    out: list[int] = []
    for _ in range(m):
        x, y, q = next(data), next(data), next(data)
        out.append(first_on_path(x, y, q, hld, seg))
    sys.stdout.write('\n'.join(map(str, out)) + '\n')


if __name__ == "__main__":
    solve()
