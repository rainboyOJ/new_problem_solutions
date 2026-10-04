#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:34
# update_at: 2026-09-30 18:34

import sys
from bisect import bisect_left, bisect_right
from collections import defaultdict
from collections.abc import Iterator

# 每个信仰一份结构：(dfn 升序位置表, 求和树状数组, 最大值线段树)。
# 信仰成员按 dfn 排序后是静态的，秩可随时二分得到，因此不必动态开点。
Tree = tuple[list[int], list[int], list[int]]
HLD = tuple[list[int], list[int], list[int], list[int]]  # (链顶, 深度, 父亲, dfn)


def build_hld(n: int, adj: list[list[int]], root: int = 1) -> HLD:
    """树链剖分：先算子树大小与重儿子，再按重链优先顺序给 dfn 编号。"""
    parent = [0] * (n + 1)
    dep = [0] * (n + 1)
    order: list[int] = []
    stack = [root]
    while stack:                                    # 迭代 DFS，避免链形树爆递归
        u = stack.pop()
        order.append(u)
        for v in adj[u]:
            if v != parent[u]:
                parent[v] = u
                dep[v] = dep[u] + 1
                stack.append(v)

    size = [1] * (n + 1)
    heavy = [0] * (n + 1)                           # 重儿子：子树最大的儿子
    for u in reversed(order):                       # 逆 DFS 序保证儿子先算完
        top, big = 0, 0
        for v in adj[u]:
            if v != parent[u]:
                size[u] += size[v]
                if size[v] > top:
                    top, big = size[v], v
        heavy[u] = big

    dfn = [0] * (n + 1)
    head = [0] * (n + 1)
    head[root] = root
    todo = [root]
    clock = 0
    while todo:                                     # 每条链拿到连续的一段 dfn
        u = todo.pop()
        h = head[u]
        w = u
        while w:                                    # 沿重链一路走到叶子
            dfn[w] = clock
            clock += 1
            head[w] = h
            for v in adj[w]:                        # 轻儿子各自成链，稍后处理
                if v != parent[w] and v != heavy[w]:
                    head[v] = v
                    todo.append(v)
            w = heavy[w]
    return head, dep, parent, dfn


def path_spans(x: int, y: int, hld: HLD) -> Iterator[tuple[int, int]]:
    """把树上 x→y 的路径拆成若干段连续 dfn 闭区间（树链剖分标准拆法）。"""
    head, dep, parent, dfn = hld
    while head[x] != head[y]:                       # 不在同一条链上时，先走链顶更深的一侧
        if dep[head[x]] < dep[head[y]]:
            x, y = y, x
        yield dfn[head[x]], dfn[x]
        x = parent[head[x]]
    if dep[x] > dep[y]:                             # 同链时浅的是 LCA
        x, y = y, x
    yield dfn[x], dfn[y]


def fenwick_add(bit: list[int], i: int, delta: int) -> None:
    """树状数组单点加：第 i 个位置（1 起）增加 delta。"""
    while i < len(bit):
        bit[i] += delta
        i += i & -i


def fenwick_sum(bit: list[int], i: int) -> int:
    """树状数组前缀和：前 i 个元素（1 起）之和。"""
    total = 0
    while i:
        total += bit[i]
        i -= i & -i
    return total


def seg_max(seg: list[int], size: int, l: int, r: int) -> int:
    """线段树区间最大值：半开区间 [l, r) 叶子的最大值，空区间记 0。"""
    res = 0
    l += size
    r += size
    while l < r:
        if l & 1:
            res = max(res, seg[l])
            l += 1
        if r & 1:
            r -= 1
            res = max(res, seg[r])
        l >>= 1
        r >>= 1
    return res


def paint(tree: Tree, x: int, v: int, dfn: list[int]) -> None:
    """把城市 x 在某信仰结构里的取值改成 v（0 表示当前不信仰它）。"""
    pos, bit, seg = tree
    i = bisect_left(pos, dfn[x])                    # dfn 在位置表里必然存在，二分即得秩
    size = len(seg) >> 1
    j = i + size
    delta = v - seg[j]                              # 树状数组只记增量，旧值就存在叶子里
    if delta:
        seg[j] = v
        while j > 1:                                # 叶子回溯更新整条链上的最大值
            j >>= 1
            seg[j] = max(seg[j << 1], seg[j << 1 | 1])
        fenwick_add(bit, i + 1, delta)


def query_sum(x: int, y: int, c: int, trees: dict[int, Tree], hld: HLD) -> int:
    """查询 x→y 路径上信仰 c 的城市评级总和。"""
    pos, bit, _ = trees[c]
    return sum(
        fenwick_sum(bit, bisect_right(pos, r)) - fenwick_sum(bit, bisect_left(pos, l))
        for l, r in path_spans(x, y, hld)           # 每段区间二分出秩范围再求和
    )


def query_max(x: int, y: int, c: int, trees: dict[int, Tree], hld: HLD) -> int:
    """查询 x→y 路径上信仰 c 的城市评级最大值。"""
    pos, _, seg = trees[c]
    size = len(seg) >> 1
    return max(
        seg_max(seg, size, bisect_left(pos, l), bisect_right(pos, r))
        for l, r in path_spans(x, y, hld)           # 评级恒为正，空段记 0 不影响答案
    )


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    it = iter(tokens)
    n = int(next(it))
    q = int(next(it))
    weight = [0] * (n + 1)                          # 当前评级
    rel = [0] * (n + 1)                             # 当前信仰
    for i in range(1, n + 1):
        weight[i] = int(next(it))
        rel[i] = int(next(it))

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a = int(next(it))
        b = int(next(it))
        adj[a].append(b)
        adj[b].append(a)

    # 第一遍扫 CC：记下每座城市出现过的信仰，成员静态，按 dfn 升序建位置表。
    ever: dict[int, list[int]] = defaultdict(list)
    for i in range(1, n + 1):
        ever[rel[i]].append(i)

    ops: list[tuple[bytes, int, int]] = []
    for _ in range(q):
        op = next(it)
        x = int(next(it))
        y = int(next(it))
        ops.append((op, x, y))
        if op == b"CC":
            ever[y].append(x)

    hld = build_hld(n, adj)
    dfn = hld[3]

    trees: dict[int, Tree] = {}
    for c, members in ever.items():
        members.sort(key=dfn.__getitem__)
        size = 1 << (len(members) - 1).bit_length()  # 完全二叉树叶子数取 2 的幂
        trees[c] = ([dfn[x] for x in members], [0] * (len(members) + 1), [0] * (2 * size))
    for i in range(1, n + 1):                        # 初始全员在自己的信仰里
        paint(trees[rel[i]], i, weight[i], dfn)

    out: list[str] = []
    for op, x, y in ops:
        if op == b"QS":
            out.append(str(query_sum(x, y, rel[x], trees, hld)))
        elif op == b"QM":
            out.append(str(query_max(x, y, rel[x], trees, hld)))
        elif op == b"CW":
            weight[x] = y
            paint(trees[rel[x]], x, y, dfn)
        else:                                        # CC x c：先退出旧信仰，再加入新信仰
            if rel[x] != y:
                paint(trees[rel[x]], x, 0, dfn)
                rel[x] = y
                paint(trees[y], x, weight[x], dfn)

    print("\n".join(out))


if __name__ == "__main__":
    solve()
