#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:30
# update_at: 2026-10-07 20:30

import sys

# 类型别名：链式前向星三元组 (head, to, nxt)；第 i 条输入边占弧 2i 与 2i+1
# head/nxt 里的 -1 是哨兵，表示"后面没有弧了"
type Star = tuple[list[int], list[int], list[int]]

# 两个等长的 int 列表：(并查集父亲, 每块大小) 或 (桥对应子树根, DFS 子树大小)
type ListPair = tuple[list[int], list[int]]


def build_star(n: int, m: int, ends: list[int]) -> Star:
    """建无向图的链式前向星；第 i 条输入边的两端是 ends[2i]、ends[2i+1]。"""
    head = [-1] * n
    to = [0] * (2 * m)
    nxt = [-1] * (2 * m)
    for i in range(m):
        u, v = ends[2 * i], ends[2 * i + 1]
        e = i << 1
        to[e], nxt[e], head[u] = v, head[u], e
        to[e + 1], nxt[e + 1], head[v] = u, head[v], e + 1
    return head, to, nxt


def find_root(fa: list[int], x: int) -> int:
    """并查集找根（带路径折半）；fa 上是父亲，根的父亲是自己。"""
    while fa[x] != x:
        fa[x] = fa[fa[x]]
        x = fa[x]
    return x


def build_dsu(n: int, m: int, ends: list[int]) -> ListPair:
    """并查集 + 每块大小：只有根的 sz 有效，用来 O(1) 取任意点所在连通块大小。"""
    fa = list(range(n))
    sz = [1] * n
    for i in range(m):
        a, b = find_root(fa, ends[2 * i]), find_root(fa, ends[2 * i + 1])
        if a == b:
            continue
        if sz[a] < sz[b]:
            a, b = b, a
        fa[b] = a
        sz[a] += sz[b]
    return fa, sz


def count_unreachable0(n: int, fa: list[int], sz: list[int]) -> int:
    """T0 = C(n,2) - Σ 每块 C(块大小,2)：删边前就已经互不可达的无序点对数。"""
    total = n * (n - 1) // 2
    for r in range(n):
        if fa[r] == r:                       # 只在根上统计一次
            total -= sz[r] * (sz[r] - 1) // 2
    return total


def find_bridges(n: int, m: int, star: Star) -> ListPair:
    """迭代式 Tarjan：返回 (bridge_child, sub)，对应 C++ 版的同名数组。

    bridge_child[x] = 边 x 是桥时被切下的那侧子树根（否则 -1）；sub[v] = DFS 子树点数。
    必须按「父边编号」跳过父边（e >> 1），否则平行重边会被误判成桥；自环不影响连通性。
    """
    head, to, nxt = star
    dfn = [0] * n            # DFS 序，0 表示未访问
    low = [0] * n            # 能回溯到的最小 dfn
    pe = [-1] * n            # DFS 树中的父边编号
    sub = [0] * n            # DFS 树子树点数
    it = head[:]             # 当前出弧指针
    bridge_child = [-1] * m
    timer = 0
    for s in range(n):
        if dfn[s]:
            continue
        timer += 1
        dfn[s] = low[s] = timer
        sub[s] = 1
        stack = [s]
        while stack:
            u = stack[-1]
            e = it[u]
            if e != -1:
                it[u] = nxt[e]
                if (e >> 1) == pe[u]:
                    continue             # 父边的两个方向都不走
                v = to[e]
                if dfn[v] == 0:
                    timer += 1
                    dfn[v] = low[v] = timer
                    sub[v] = 1
                    pe[v] = e >> 1
                    it[v] = head[v]
                    stack.append(v)
                elif dfn[v] < low[u]:
                    low[u] = dfn[v]      # 返祖边（含重边里指向祖先的那一条）
            else:
                stack.pop()              # u 的出弧走完，回溯到父亲 p
                if stack:
                    p = stack[-1]
                    sub[p] += sub[u]
                    if low[u] < low[p]:
                        low[p] = low[u]
                    if low[u] > dfn[p]:                 # 子树回不到 p → 父边是桥
                        bridge_child[pe[u]] = u         # 记下切走的那侧子树根
    return bridge_child, sub


def answer_queries(fa: list[int], sz: list[int], sub: list[int], bridge_child: list[int],
                   unreachable0: int, queries: list[int]) -> list[str]:
    """逐条回答询问：桥的答案 = T0 + s*(C-s)，其余边就是 T0；输出只保留后三位。"""
    out: list[str] = []
    for x in queries:
        ans = unreachable0
        cuts = bridge_child[x]
        if cuts >= 0:                              # 是桥：连通块被切成 s 与 C-s 两块
            block = sz[find_root(fa, cuts)]        # 该边所在连通块大小 C
            ans += sub[cuts] * (block - sub[cuts])  # 新增互不可达点对 s*(C-s)
        out.append(str(ans % 1000))                # 题面要求只保留后三位
    return out


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, Q = next(data), next(data), next(data)

    ends = [next(data) for _ in range(2 * m)]     # 第 i 条边的两端紧挨着
    queries = [next(data) for _ in range(Q)]

    star = build_star(n, m, ends)
    fa, sz = build_dsu(n, m, ends)
    unreachable0 = count_unreachable0(n, fa, sz)
    bridge_child, sub = find_bridges(n, m, star)

    answers = answer_queries(fa, sz, sub, bridge_child, unreachable0, queries)
    sys.stdout.write('\n'.join(answers) + '\n')


if __name__ == "__main__":
    solve()
