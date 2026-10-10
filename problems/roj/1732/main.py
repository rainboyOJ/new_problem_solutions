#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:45
# update_at: 2026-10-07 20:45

import sys
from itertools import groupby

# 核心结论：把全部①要求原样当边连成图 G0，则「合法情报网存在」⇔ 每条②要求 (a,b)
# 在 G0 里都不可达。因为可达性有传递性 ⇒ 任何合法图都必须包含 TC(G0)；反过来取
# G = G0 就合法，而它的边数 = m ≤ n+m+t。于是问题只剩「①图上的 t 次可达性」。
# 缩点后：a 能到 b ⇔ comp[a] 能到 comp[b]（同分量时恒真）。

BLK = 4096  # 可达性分块宽度：一次只追踪「编号落在 [lo, lo+BLK) 内」的目的地

type Edges = list[tuple[int, int]]  # 要求表：每项是一个 (a, b) 点对
type Adj = list[list[int]]          # 邻接表：Adj[u] 是 u 的出边终点列表


def load() -> tuple[int, Edges, Edges]:
    """按输入格式顺序取出 n、①要求表、②要求表。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)
    req1: Edges = [(next(data), next(data)) for _ in range(m)]
    t = next(data)
    req2: Edges = [(next(data), next(data)) for _ in range(t)]
    return n, req1, req2


def scc(n: int, req1: Edges) -> tuple[list[int], int]:
    """Tarjan 求强连通分量，返回 (每个点的分量号, 分量总数)。

    分量号按弹栈顺序给出：跨分量的边 u→v 恒满足 comp[u] > comp[v]，
    即分量号**升序**恰好是缩点 DAG 的逆拓扑序（后继都已算好）。
    用显式调用栈代替递归，n=1e5 的链也不会爆栈。
    """
    adj: Adj = [[] for _ in range(n + 1)]
    for a, b in req1:
        adj[a].append(b)

    dfn = [0] * (n + 1)
    low = [0] * (n + 1)
    comp = [0] * (n + 1)
    onstk = bytearray(n + 1)
    stk: list[int] = []  # Tarjan 栈
    timer = 0
    cc = 0

    for s in range(1, n + 1):
        if dfn[s]:
            continue
        timer += 1
        dfn[s] = low[s] = timer
        stk.append(s)
        onstk[s] = 1
        call_node = [s]  # 显式调用栈：节点
        call_i = [0]     # 与之平行：该节点下一条待访问的邻边下标
        while call_node:
            u = call_node[-1]
            i = call_i[-1]
            if i < len(adj[u]):
                call_i[-1] = i + 1
                v = adj[u][i]
                if not dfn[v]:
                    timer += 1
                    dfn[v] = low[v] = timer
                    stk.append(v)
                    onstk[v] = 1
                    call_node.append(v)
                    call_i.append(0)
                elif onstk[v] and dfn[v] < low[u]:
                    low[u] = dfn[v]  # 回边：用 dfn 更新
            else:
                call_node.pop()
                call_i.pop()
                if low[u] == dfn[u]:  # u 是所在 SCC 的根 → 弹栈定型
                    while True:
                        w = stk.pop()
                        onstk[w] = 0
                        comp[w] = cc
                        if w == u:
                            break
                    cc += 1
                if call_node:
                    p = call_node[-1]
                    if low[u] < low[p]:
                        low[p] = low[u]  # 子孙的 low 回传给父节点
    return comp, cc


def dag_adj(comp: list[int], cnt: int, req1: Edges) -> Adj:
    """缩点后的 DAG 邻接表：去掉自环（同分量内永远互相可达），跨分量边去重。"""
    seen: list[set[int]] = [set() for _ in range(cnt)]
    for a, b in req1:
        if comp[a] != comp[b]:
            seen[comp[a]].add(comp[b])
    return [list(s) for s in seen]


def violated(comp: list[int], cnt: int, nxt: Adj, req2: Edges) -> bool:
    """②要求是否有被①图的传递闭包满足：满足任意一条就说明无解。

    先做快速判据：a、b 落在同一个分量 ⇒ 同属一个强连通分量、互相可达（a==b 时
    还需分量里还有别的点才成环）⇒ 必然无解。

    剩下的点对逐个用位集合判：缩点 DAG 上 c 的可达集第 d 位为 1 表示 comp[c] ⇝ comp[d]。
    按目的地分块做，一次只保留落在一块 BLK 个分量内的目的地，按分量号升序递推
        reach[c] = bit(c-lo) | ⋃ reach[d]   （c→d 为跨分量边）
    因为跨分量边总是从大编号指向小编号，升序递推时后继一定已经算好；编号 < lo 的
    行在本块恒为 0，正好等价于「本块不追踪那些目的地」。
    """
    csize = [0] * cnt
    for c in comp[1:]:
        csize[c] += 1

    for a, b in req2:
        ca, cb = comp[a], comp[b]
        same_comp = ca == cb
        if same_comp and (a != b or csize[ca] > 1):
            return True

    pairs = sorted((comp[b], comp[a]) for a, b in req2)  # 按②的目标分量排序

    for blk, grp in groupby(pairs, key=lambda p: p[0] // BLK):
        lo = blk * BLK
        hi = lo + BLK  # 本块追踪的目的地区间 [lo, hi)
        reach = [0] * cnt  # 每个分量在本块内的可达目的地集合
        for c in range(lo, cnt):
            # 只有落在本块的目的地才登记成位；不在本块的 c 只继承后继的可达位
            mask = 1 << (c - lo) if c < hi else 0
            for d in nxt[c]:
                mask |= reach[d]
            reach[c] = mask
        for target, src in grp:
            # target == src 只可能是「a==b 且分量大小为 1」，已在快速判据里排除；
            # 位集合里第 src 位总为 1，若不排除就会把「自己到自己」误判成可达。
            reachable = src != target and reach[src] >> (target - lo) & 1
            if reachable:
                return True
    return False


def solve() -> None:
    n, req1, req2 = load()
    comp, cnt = scc(n, req1)

    out: list[str] = []
    if violated(comp, cnt, dag_adj(comp, cnt, req1), req2):
        out.append("NO")
    else:
        # G0 自己就是合法解：m 条①要求原样当电话线输出，P = m ≤ n+m+t
        out += ["YES", str(len(req1))]
        out += [f"{a} {b}" for a, b in req1]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
