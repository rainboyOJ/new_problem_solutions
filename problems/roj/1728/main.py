#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 19:16
# update_at: 2026-10-07 19:16

import sys
from array import array

LIMIT = 10**9  # 值域上界：任何位置的下界超过它就没有合法方案

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type IntArr = array                                          # 4 字节整型数组，压住图的规模
type Graph = tuple[IntArr, IntArr, IntArr, IntArr, int]      # (head, eto, enxt, indeg, 点数)


def decompose_range(l: int, r: int, sz: int) -> list[int]:
    """把 1-indexed 闭区间 [l, r] 拆成 O(log n) 个线段树节点编号；空区间返回空表。"""
    nodes = []
    lo, hi = l - 1 + sz, r - 1 + sz + 1
    while lo < hi:
        if lo & 1:
            nodes.append(lo)
            lo += 1
        if hi & 1:
            hi -= 1
            nodes.append(hi)
        lo >>= 1
        hi >>= 1
    return nodes


def add_edge(head: IntArr, eto: IntArr, enxt: IntArr, indeg: IntArr, u: int, v: int) -> None:
    """加一条 u -> v 的边；边权不落地，交给终点类型判定（理由见 build_graph）。"""
    eto.append(v)
    enxt.append(head[u])
    head[u] = len(eto) - 1
    indeg[v] += 1


def build_graph(sz: int, m: int, ql: IntArr, qr: IntArr,
                xs: IntArr, xoff: IntArr) -> Graph:
    """把每条信息翻译成差分约束图，返回 (head, eto, enxt, indeg, 点数)。

    边 u -> v 表示 a[v] >= a[u] + w。边权只有 0/1，且恰好由终点类型决定：
    指向条件点（编号 >= segN）的边权为 1，那就是“严格大于”贡献的 +1；
    指向线段树节点的边权为 0。所以不必再存一份边权数组。
    """
    segN = 2 * sz
    V = segN - 1 + m                       # 条件点编号 segN .. segN+m-1
    head = array('i', [0]) * (V + 1)
    indeg = array('i', [0]) * (V + 1)
    eto = array('i', [0])                  # 下标 0 当“无边”哨兵
    enxt = array('i', [0])

    for i in range(2, segN):
        add_edge(head, eto, enxt, indeg, i, i >> 1)       # 儿子 -> 父亲，权 0

    for q in range(m):
        p = segN + q                       # 条件点：含义是“x 集合中的最小值”
        prev = ql[q]
        for j in range(xoff[q], xoff[q + 1]):
            x = xs[j]
            for node in decompose_range(prev, x - 1, sz):  # 剩下的位置 -> p，权 1
                add_edge(head, eto, enxt, indeg, node, p)
            add_edge(head, eto, enxt, indeg, p, sz + x - 1)  # p -> x_i，权 0
            prev = x + 1
        for node in decompose_range(prev, qr[q], sz):      # 末尾那段空隙
            add_edge(head, eto, enxt, indeg, node, p)

    return head, eto, enxt, indeg, V


def topo_bounds(n: int, sz: int, known: dict[int, int], graph: Graph) -> list[int] | None:
    """按拓扑序把下界沿出边推出去，返回每个位置的下界；约束矛盾时返回 None。

    矛盾的三种来源：下界超出值域、已知位置被逼着大于给定值、约束成环。
    """
    head, eto, enxt, indeg, V = graph
    segN = 2 * sz
    val = [0] * (V + 1)
    for leaf, d in known.items():
        val[leaf] = d                      # 已知位置以精确值当初始下界

    que = [u for u in range(1, V + 1) if indeg[u] == 0]
    for u in que:
        if val[u] < 1:
            val[u] = 1                     # 没有任何约束的点取下界 1

    qi = 0
    while qi < len(que):
        u = que[qi]
        qi += 1
        vu = val[u]
        d = known.get(u, 0)
        if vu > LIMIT or (d and vu > d):   # 下界越界 / 与已知精确值冲突
            return None
        e = head[u]
        while e:
            v = eto[e]
            nv = vu + 1 if v >= segN else vu   # 指向条件点的边权 1，其余 0
            if val[v] < nv:
                val[v] = nv
            indeg[v] -= 1
            if indeg[v] == 0:
                que.append(v)
            e = enxt[e]

    if len(que) != V:                      # 还有没被剥掉的点 → 约束成环
        return None
    for i in range(1, n + 1):
        v = val[sz + i - 1]
        if v < 1 or v > LIMIT:
            return None
    return val


def solve() -> None:
    # 先整体转成紧凑整型数组再顺序消费：`split()` 出来的字节串列表有几千万字节，
    # 直接 map 会让它一直挂着不放，这里让它转完就释放。
    data = iter(array('i', map(int, sys.stdin.buffer.read().split())))
    n, s, m = next(data), next(data), next(data)

    sz = 1
    while sz < n:
        sz <<= 1                           # 位置 i 的叶子编号是 sz + i - 1

    known: dict[int, int] = {}
    for _ in range(s):
        p, d = next(data), next(data)
        known[sz + p - 1] = d

    ql, qr = array('i', [0]) * m, array('i', [0]) * m
    xoff = array('i', [0]) * (m + 1)
    xs: IntArr = array('i')                # 所有信息的 x 扁平存储
    for q in range(m):
        ql[q], qr[q] = next(data), next(data)
        k = next(data)                     # 题面的 k_i
        xoff[q] = len(xs)
        xs.extend([next(data) for _ in range(k)])
    xoff[m] = len(xs)

    val = topo_bounds(n, sz, known, build_graph(sz, m, ql, qr, xs, xoff))
    if val is None:
        print("NIE")
        return
    print("TAK")
    print(" ".join(map(str, (val[sz + i - 1] for i in range(1, n + 1)))))


if __name__ == "__main__":
    solve()
