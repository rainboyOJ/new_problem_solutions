#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 22:05
# update_at: 2026-10-07 22:27

import sys

type Graph = tuple[list[int], list[int], list[int]]   # 原图 CSR：(区间表, 对端, 边号)
type Blocks = tuple[list[int], list[int], list[int], list[int]]  # (块号, 父边, 顶点序, 块区间表)


def build_graph(n: int, eu: list[int], ev: list[int]) -> Graph:
    """建原图 CSR 邻接：每个点的邻居按边的输入顺序排列（决定生成树与后续输出顺序）。"""
    off = [0] * (n + 1)
    for a in eu:
        off[a + 1] += 1
    for b in ev:
        off[b + 1] += 1
    for v in range(n):
        off[v + 1] += off[v]
    cur = off[:]                      # 每个点下一个可写的位置
    gto = [0] * (2 * len(eu))
    geid = [0] * (2 * len(eu))
    for i in range(len(eu)):
        a, b = eu[i], ev[i]
        p = cur[a]
        cur[a] = p + 1
        q = cur[b]
        cur[b] = q + 1
        gto[p], geid[p] = b, i
        gto[q], geid[q] = a, i
    return off, gto, geid


def find_blocks(n: int, graph: Graph) -> Blocks:
    """划分连通块，并顺带做深搜生成树：记录每个点的父边与块内出栈顺序。"""
    off, gto, geid = graph
    comp, par, order, beg = [-1] * n, [-1] * n, [], []
    ncomp = 0
    for s in range(n):
        if comp[s] != -1:
            continue
        beg.append(len(order))
        comp[s] = ncomp
        stack = [s]
        while stack:
            v = stack.pop()
            order.append(v)
            for p in range(off[v], off[v + 1]):
                to = gto[p]
                if comp[to] == -1:
                    comp[to] = ncomp
                    par[to] = geid[p]     # 父边 = 第一次发现这个点的那条边
                    stack.append(to)
        ncomp += 1
    beg.append(len(order))
    return comp, par, order, beg


def group_edges(m: int, ncomp: int, comp: list[int], eu: list[int]) -> tuple[list[int], list[int]]:
    """把边按所属连通块分组（计数排序，块内保持输入顺序），返回 (块区间表, 边的重排)。"""
    beg = [0] * (ncomp + 1)
    for i in range(m):
        beg[comp[eu[i]] + 1] += 1
    for c in range(ncomp):
        beg[c + 1] += beg[c]
    cur = beg[:]
    order = [0] * m
    for i in range(m):
        c = comp[eu[i]]
        order[cur[c]] = i
        cur[c] += 1
    return beg, order


def aux_edges(block: list[int], loc: list[int], par: list[int], eu: list[int], ev: list[int],
              s_edges: list[int], sdeg: list[int], n_odd: int) -> tuple[list[int], list[int]]:
    """辅助图 M 的边表 (ma, mb)。

    三条来源缺一不可：生成树的每条树边放 2 份（只为连通，不改奇偶）、块内所有 c=1 的边各 1 份、
    奇数度点各接一条连向虚点的边（虚点用块内编号 nC 表示）。
    """
    nC = len(block)
    ma: list[int] = []
    mb: list[int] = []
    for v in block:
        pe = par[v]
        if pe < 0:
            continue                       # 生成树的根没有父边
        u = ev[pe] if eu[pe] == v else eu[pe]
        lu, lv = loc[u], loc[v]
        ma.append(lu)
        mb.append(lv)
        ma.append(lu)
        mb.append(lv)
    for e in s_edges:
        ma.append(loc[eu[e]])
        mb.append(loc[ev[e]])
    if n_odd:
        for i, v in enumerate(block):
            if sdeg[v]:
                ma.append(nC)              # 虚点：切分路径的刀口
                mb.append(i)
    return ma, mb


def euler_seq(ma: list[int], mb: list[int], mvtx: int, base: int) -> list[int]:
    """迭代求 M 的欧拉回路，返回自 base 出发覆盖全边、首尾相同的顶点序列。"""
    me = len(ma)
    off = [0] * (mvtx + 1)
    for a in ma:
        off[a + 1] += 1
    for b in mb:
        off[b + 1] += 1
    for v in range(mvtx):
        off[v + 1] += off[v]
    cur = off[:]
    nbr = [0] * (2 * me)                   # 每条半边通向的对端
    twin = [0] * (2 * me)                  # 同一条边另一条半边的位置
    used = bytearray(2 * me)
    for i in range(me):
        a, b = ma[i], mb[i]
        p = cur[a]
        cur[a] = p + 1
        q = cur[b]
        cur[b] = q + 1
        nbr[p], nbr[q] = b, a
        twin[p], twin[q] = q, p
    ptr = off[:]
    seq: list[int] = []
    stack = [base]
    while stack:
        v = stack[-1]
        p = ptr[v]
        end = off[v + 1]
        while p < end and used[p]:
            p += 1
        if p == end:
            ptr[v] = end       # 剩余半边全走过：回退过的旧位置不再重复扫描（否则退化成 O(deg^2)）
            seq.append(v)
            stack.pop()
        else:
            ptr[v] = p + 1
            used[p] = 1
            used[twin[p]] = 1
            stack.append(nbr[p])
    seq.reverse()
    return seq


def path_line(seg: list[int], block: list[int]) -> str:
    """把一段局部编号渲染成题目要求的一行：`l v1 v2 ... vl`（编号换回原图的 1 起）。"""
    return ' '.join([str(len(seg))] + [str(block[x] + 1) for x in seg])


def solve_case(n: int, m: int, eu: list[int], ev: list[int], ec: list[int]) -> list[str]:
    """一组数据的全部输出行：第一行是人数 K，之后是每个人走过的路径。"""
    sdeg = [0] * n                         # sdeg[v]：与 v 相邻的 c=1 边数 mod 2
    for a, b, ci in zip(eu, ev, ec):
        sdeg[a] ^= ci
        sdeg[b] ^= ci

    graph = build_graph(n, eu, ev)
    comp, par, order, vbeg = find_blocks(n, graph)
    ncomp = len(vbeg) - 1
    ebeg, eord = group_edges(m, ncomp, comp, eu)
    has_s = [False] * ncomp
    for i in range(m):
        if ec[i]:
            has_s[comp[eu[i]]] = True

    total_k = 0                            # 答案下界 = 每块奇数度点数 / 2，无奇数度点也要 1 趟
    for c in range(ncomp):
        if not has_s[c]:
            continue
        n_odd = sum(1 for v in order[vbeg[c]:vbeg[c + 1]] if sdeg[v])
        total_k += n_odd // 2 if n_odd else 1

    out = [str(total_k)]
    loc = [0] * n                          # 原图点 -> 块内局部编号
    for c in range(ncomp):
        if not has_s[c]:
            continue
        block = order[vbeg[c]:vbeg[c + 1]]
        for i, v in enumerate(block):
            loc[v] = i
        n_odd = sum(1 for v in block if sdeg[v])
        s_edges = [eord[k] for k in range(ebeg[c], ebeg[c + 1]) if ec[eord[k]]]
        ma, mb = aux_edges(block, loc, par, eu, ev, s_edges, sdeg, n_odd)
        nC = len(block)
        xv = nC if n_odd else 0            # 虚点：奇数度点成对时的拐点（编号 nC）
        mvtx = nC + 1 if n_odd else nC
        seq = euler_seq(ma, mb, mvtx, xv)
        if not n_odd:
            # 整块没有奇度点：这一整条回路就是 1 个人的走法（首点重复出现在末位）
            out.append(path_line(seq, block))
            continue
        prev = 0                           # seq[0] 就是虚点，两处虚点之间是 1 个人
        for i in range(1, len(seq)):
            if seq[i] != xv:
                continue
            if prev + 1 <= i - 1:          # 非空段才是一段真实路径
                out.append(path_line(seq[prev + 1:i], block))
            prev = i
    return out


def solve() -> None:
    vals = list(map(int, sys.stdin.buffer.read().split()))
    if not vals:
        return
    pos = 0
    T = vals[pos]
    pos += 1
    out: list[str] = []
    for _ in range(T):
        n, m = vals[pos], vals[pos + 1]
        pos += 2
        block = vals[pos:pos + 3 * m]      # 每 3 个数一条边：a, b, c
        pos += 3 * m
        eu = [x - 1 for x in block[0::3]]
        ev = [x - 1 for x in block[1::3]]
        ec = block[2::3]
        out += solve_case(n, m, eu, ev, ec)
    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
