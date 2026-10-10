#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 22:30
# update_at: 2026-10-07 22:30

import sys
from array import array
from bisect import bisect_left
from collections.abc import Iterator

CHUNK = 4096  # 输出每次写多少行：1e6 行一次性 join 会多占几十 MB

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type DataIter = Iterator[int]                     # 顺序消费的整数流
type Graph = tuple[array, array, array, array]    # (head, nxt, to, wt) 链式前向星
type Rooted = tuple[array, array, array, array]   # (fa, parw, dis, order) 自根向下的信息
type Arms = tuple[array, array, array, array, array]  # (f1, f2, hc, dia, src) 树形 DP 结果
type Chains = tuple[array, array, array]          # (pos, chend, chain_dis) 长链剖分展开


def build_graph(n: int, data: DataIter) -> Graph:
    """把 n-1 条边读成链式前向星，边 e 与 e+1（e 为偶数）互为反向边。"""
    head = array('i', bytes(4 * (n + 1)))   # head[u]：u 的第一条边，0 表示没有
    nxt = array('i', bytes(8 * n))          # 下一条边，编号最大 2n-1
    to = array('i', bytes(8 * n))           # 边的另一个端点
    wt = array('i', bytes(8 * n))           # 边权
    for e in range(2, 2 * n, 2):
        u, v, w = next(data), next(data), next(data)
        to[e], wt[e], nxt[e], head[u] = v, w, head[u], e
        to[e + 1], wt[e + 1], nxt[e + 1], head[v] = u, w, head[v], e + 1
    return head, nxt, to, wt


def rooted(n: int, graph: Graph) -> Rooted:
    """以 1 为根做迭代 BFS：父亲 fa、父边权 parw、到根距离 dis、BFS 序 order。"""
    head, nxt, to, wt = graph
    fa = array('i', bytes(4 * (n + 1)))
    parw = array('i', bytes(4 * (n + 1)))
    dis = array('q', bytes(8 * (n + 1)))    # 距离最大 1e6*1e4=1e10，必须 64 位
    order = array('i', bytes(4 * (n + 1)))
    order[0] = 1
    qt = 1
    for qh in range(n):
        u = order[qh]
        du, pu, e = dis[u], fa[u], head[u]
        while e:
            v = to[e]
            if v != pu:                     # 树上无重边，不回走父亲即不重复访问
                fa[v], parw[v], dis[v], order[qt] = u, wt[e], du + wt[e], v
                qt += 1
            e = nxt[e]
    return fa, parw, dis, order


def arms(n: int, fa: array, parw: array, dis: array, order: array) -> Arms:
    """逆 BFS 序（即自底向上）求每个子树的 f1、f2、重孩子 hc、直径 dia、来源 src。

    src[u] = 直径继承自哪个孩子；为 0 表示直径经过 u 本身，最优点需要在链上重找。
    """
    f1 = array('q', bytes(8 * (n + 1)))     # f1[u]：u 向下最长臂长
    f2 = array('q', bytes(8 * (n + 1)))     # f2[u]：次长臂长（来自另一个孩子，无则 0）
    hc = array('i', bytes(4 * (n + 1)))     # hc[u]：最长臂所在的孩子，即长链的重孩子
    dia = array('q', bytes(8 * (n + 1)))    # dia[u]：子树 u 的直径
    src = array('i', bytes(4 * (n + 1)))    # 直径来源孩子，0 表示要重算答案
    for k in range(n - 1, -1, -1):
        u = order[k]
        through = f1[u] + f2[u]             # 经过 u 本身的最长路径
        if through >= dia[u]:
            dia[u] = through
            src[u] = 0
        if u == 1:
            continue
        par = fa[u]
        val = f1[u] + parw[u]               # u 这条臂延伸到父亲之后的长度
        if val > f1[par]:
            f2[par], f1[par], hc[par] = f1[par], val, u
        elif val > f2[par]:
            f2[par] = val
        if dia[u] > dia[par]:
            dia[par], src[par] = dia[u], u
    return f1, f2, hc, dia, src


def chains(n: int, order: array, fa: array, hc: array, dis: array) -> Chains:
    """长链剖分：每条链自上而下展开，链上 dis 严格递增，可以直接二分。"""
    pos = array('i', bytes(4 * (n + 1)))    # pos[u]：u 在 chain_dis 里的下标
    chend = array('i', bytes(4 * (n + 1)))  # chend[u]：u 所在链的链底下标
    chain_dis = array('q', bytes(8 * (n + 1)))
    ptr = 0
    for k in range(n):
        u = order[k]
        if u != 1 and hc[fa[u]] == u:
            continue                        # 不是链顶，已随链顶一起展开过
        v = u
        while v:
            pos[v], chain_dis[ptr] = ptr, dis[v]
            ptr += 1
            v = hc[v]
        last = ptr - 1
        v = u
        while v:
            chend[v] = last
            v = hc[v]
    return pos, chend, chain_dis


def answers(n: int, order: array, dis: array, arm: Arms, chain: Chains) -> array:
    """逆 BFS 序求每个子树的能力（半径）。

    直径来自孩子时半径直接继承；直径经过 u 时，两条最长臂端点 p1（链底）、p2
    确定唯一一条直径，最优点就在 p1 到 u 这一段上，用二分找满足
    2*d(p1,x) >= D 的最低点 x，取 x 与其上一个点的较小值。
    """
    f1, f2, _hc, dia, src = arm              # _hc 只在 chains() 里用到
    pos, chend, chain_dis = chain
    ans = array('q', bytes(8 * (n + 1)))
    for k in range(n - 1, -1, -1):
        u = order[k]
        c = src[u]
        if c:
            ans[u] = ans[c]                 # 直径整段落在孩子子树里，半径相同
            continue
        need = (2 * (dis[u] + f1[u]) - dia[u] + 1) // 2   # 条件 2*dis[x] >= t 的阈值
        lo, hi = pos[u], chend[u]
        q = bisect_left(chain_dis, need, lo, hi + 1)
        best = f2[u] + chain_dis[q] - dis[u]              # d(x,p2) 是这一侧的最大值
        if q > lo:
            alt = f1[u] - chain_dis[q - 1] + dis[u]       # 上一个点由 d(p1,·) 决定
            if alt < best:
                best = alt
        ans[u] = best
    return ans


def solve() -> None:
    # 按行边读边产出整数：改成 sys.stdin.buffer.read().split() 会把 3e6 个 token
    # 同时物化成列表，N=1e6 时白占约 100MB（实测 142MB -> 250MB），逼近 256MB 限制。
    data: DataIter = (int(x) for line in sys.stdin.buffer for x in line.split())
    n = next(data)
    graph = build_graph(n, data)
    fa, parw, dis, order = rooted(n, graph)
    arm = arms(n, fa, parw, dis, order)
    heavy_child = arm[2]                    # hc：长链剖分要用的重孩子数组
    chain = chains(n, order, fa, heavy_child, dis)
    ans = answers(n, order, dis, arm, chain)
    out = sys.stdout
    for start in range(1, n + 1, CHUNK):    # 分块写出，避免 1e6 行一次性 join
        out.write('\n'.join(map(str, ans[start:start + CHUNK])))
        out.write('\n')


if __name__ == "__main__":
    solve()
