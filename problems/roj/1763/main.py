#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 23:00
# update_at: 2026-10-07 23:00

import sys
from bisect import bisect_right
from itertools import accumulate

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Neigh = list[list[tuple[int, int]]]  # 邻接表：点 -> [(邻居, 边权)]
type Chain = list[tuple[int, int]]        # 点分树祖先链：[(祖先重心, 到它的距离)]，根在前、自己最后
type NodeList = list[list[int]]           # 每个重心管辖块内的点，按编号升序
type PrefList = list[list[int]]           # 对应的「距离」前缀和，首项为 0
type Block = tuple[NodeList, PrefList]    # 一个重心的「点表 + 距离前缀和」


def decompose(n: int, adj: Neigh) -> tuple[list[Chain], Block, Block]:
    """点分治（迭代）：返回每个点的祖先链，以及每个重心的两种「点表 + 距离前缀和」。

    comp 侧：重心 c 管辖连通块内的点到 c 的距离；
    br 侧：重心 c 管辖连通块内的点到「c 在点分树上的父亲」的距离。
    每个点被登记进祖先链的顺序就是重心被摘除的顺序，因此链天然是根在前、自己在最后。
    """
    removed = [False] * (n + 1)
    chains: list[Chain] = [[] for _ in range(n + 1)]
    comp_nodes: NodeList = [[] for _ in range(n + 1)]
    comp_prefs: PrefList = [[] for _ in range(n + 1)]
    br_nodes: NodeList = [[] for _ in range(n + 1)]
    br_prefs: PrefList = [[] for _ in range(n + 1)]
    pending: list[tuple[list[int], list[int]] | None] = [None] * (n + 1)  # 分支代表 -> 待转交的 br 侧数据
    par = [0] * (n + 1)     # 上一次 BFS 的父指针（各步复用）
    size = [0] * (n + 1)    # 连通块内以 start 为根时的子树大小
    dist = [0] * (n + 1)    # 到当前重心的距离
    branch = [0] * (n + 1)  # 点属于重心的哪个邻居分支（分支代表 = 那个邻居）

    stack = [1]
    while stack:
        start = stack.pop()

        # 1) BFS 收集本连通块，并得到以 start 为根的父子关系
        #    （边遍历边扩容：Python 的 list 迭代会看到新追加的元素）
        order = [start]
        par[start] = 0
        for u in order:
            pu = par[u]
            for v, _w in adj[u]:
                if v != pu and not removed[v]:
                    par[v] = u
                    order.append(v)
        total = len(order)

        # 2) 逆 BFS 序求子树大小
        for u in reversed(order):
            s = 1
            pu = par[u]
            for v, _w in adj[u]:
                if v != pu and not removed[v]:
                    s += size[v]
            size[u] = s

        # 3) 从 start 沿「大小 > total/2」的重儿子往下走，落点就是重心
        c = start
        while True:
            heavy = 0
            pc = par[c]
            for v, _w in adj[c]:
                if v != pc and not removed[v] and size[v] * 2 > total:
                    heavy = v
                    break
            if not heavy:
                break
            c = heavy

        # 4) 本块是上一层某分支时，父重心侧的 br 数据挂在分支代表 start 上，转交给本块重心 c
        if start != c and pending[start] is not None:
            pending[c] = pending[start]
            pending[start] = None

        # 5) 从重心 c 出发 BFS：求块内各点到 c 的距离，并记下它属于哪个邻居分支
        order = [c]
        par[c] = 0
        dist[c] = 0
        for u in order:
            du = dist[u]
            for v, w in adj[u]:
                if v != par[u] and not removed[v]:
                    par[v] = u
                    dist[v] = du + w
                    branch[v] = v if u == c else branch[u]
                    order.append(v)

        # 6) 每个分支的点按编号升序排好，配一份「到父重心 c」的距离前缀和，挂在分支代表上
        groups: dict[int, list[int]] = {}
        for v in order:
            if v != c:
                groups.setdefault(branch[v], []).append(v)
        for rep, members in groups.items():
            members.sort()
            pending[rep] = (members, list(accumulate((dist[v] for v in members), initial=0)))

        # 7) 登记本重心：升序点表 + 到 c 的距离前缀和 + 块内每点的祖先链
        order.sort()
        comp_nodes[c] = order
        comp_prefs[c] = list(accumulate((dist[v] for v in order), initial=0))
        for v in order:
            chains[v].append((c, dist[v]))

        # 8) 摘掉重心，各分支（即 c 的未摘邻居）成为独立子问题
        removed[c] = True
        stack.extend(groups)

    for c in range(1, n + 1):  # 转交完成后才认领：每个非根重心都有一份 br 侧数据
        if pending[c] is not None:
            br_nodes[c], br_prefs[c] = pending[c]
    return chains, (comp_nodes, comp_prefs), (br_nodes, br_prefs)


def range_dist(chain: Chain, L: int, R: int, comp: Block, br: Block) -> int:
    """求 Σ_{i∈[L,R]} dist(i,x)，x 的祖先链是 chain。

    记 c 为 i、x 在点分树上的 LCA，则 c 落在树上 i→x 的路径上，dist(i,x) = dist(i,c) + dist(c,x)。
    按 c 分组累加：c 恰好遍历 chain，且「LCA(i,x) = c」的点集是 comp(c) \\ comp(b)，
    b 是 c 在点分树上通往 x 的儿子；点集按编号升序，所以交 [L,R] 的点数与距离和都是一次二分。
    """
    comp_nodes, comp_prefs = comp
    br_nodes, br_prefs = br
    lo = L - 1
    tot = 0
    for j in range(len(chain) - 1):
        c, d = chain[j]      # c = LCA 这一层的重心，d = dist(c,x)
        b = chain[j + 1][0]  # b = c 通往 x 的儿子，它的块就是「要减掉的那部分」
        cn, cp = comp_nodes[c], comp_prefs[c]
        bn, bp = br_nodes[b], br_prefs[b]
        n_hi, n_lo = bisect_right(cn, R), bisect_right(cn, lo)
        m_hi, m_lo = bisect_right(bn, R), bisect_right(bn, lo)
        cnt = (n_hi - n_lo) - (m_hi - m_lo)  # comp(c) \\ comp(b) 里落在 [L,R] 的点数
        tot += (cp[n_hi] - cp[n_lo]) - (bp[m_hi] - bp[m_lo]) + cnt * d
    cn, cp = comp_nodes[chain[-1][0]], comp_prefs[chain[-1][0]]  # c = x 这一层：分支为空，d = 0
    return tot + cp[bisect_right(cn, R)] - cp[bisect_right(cn, lo)]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, online = next(data), next(data), next(data)

    adj: Neigh = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b, c = next(data), next(data), next(data)
        adj[a].append((b, c))
        adj[b].append((a, c))

    chains, comp, br = decompose(n, adj)

    out: list[str] = []
    last = 0  # 强制在线时的 lastans = 上一次答案 mod n，初值 0
    for _ in range(m):
        L, R, x = next(data), next(data), next(data)
        if online:
            L ^= last
            R ^= last
            x ^= last
        ans = range_dist(chains[x], L, R, comp, br)
        out.append(str(ans))
        last = ans % n
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
