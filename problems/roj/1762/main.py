#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 23:10
# update_at: 2026-10-08 08:51
#
# 一本通 1762《与非》：树链剖分 + 线段树维护「逐位变换」的复合。
# nand 逐位独立，一段点序列诱导的函数 F 完全由 F(0^k) 与 F(1^k) 两个掩码决定，
# 而「函数复合」满足结合律——于是不可结合的 nand 序列被搬进可结合的复合世界。
# 线段树每个结点同时存正向（dfs 序递增）与反向（dfs 序递减）两份复合结果，
# 树链剖分把树上路径拆成 O(log n) 段按顺序拼接，整体 O(n + m log^2 n)。

import sys

THRESH = 32  # 区间长度不超过它就直接逐点扫，省掉线段树查询的固定开销

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Adj = tuple[list[int], list[int]]  # CSR 邻接表：(start, nb)，start[u]..start[u+1] 是 u 的邻居区间
type Hld = tuple[list[int], list[int], list[int], list[int], list[int]]
# Hld = (par, dep, top, dfn, wd)：父结点 / 深度 / 重链链头 / 剖分下标 / 按下标存放的点权
type Seg = tuple[list[int], list[int], list[int], list[int], int]
# Seg = (fa, fb, ba, bb, size)：正向 F(0)、正向 F(1)、反向 F(0)、反向 F(1) 四张掩码表 + 叶子偏移


def build_adj(n: int, eu: list[int], ev: list[int]) -> Adj:
    """把 n-1 条无向边按计数排序压成 CSR：邻居连续存放，常数小于 list of list。"""
    deg = [0] * (n + 2)
    for e in range(1, n):
        deg[eu[e]] += 1
        deg[ev[e]] += 1
    start = [0] * (n + 2)
    acc = 0
    for u in range(1, n + 1):
        start[u] = acc
        acc += deg[u]
    start[n + 1] = acc
    fill = start[:]
    nb = [0] * (2 * (n - 1))
    for e in range(1, n):
        a, b = eu[e], ev[e]
        nb[fill[a]] = b
        fill[a] += 1
        nb[fill[b]] = a
        fill[b] += 1
    return start, nb


def heavy_light(n: int, w: list[int], adj: Adj) -> Hld:
    """树链剖分（两遍迭代，n=1e5 且可能是纯链，递归会爆栈）。

    第一遍 BFS 定父子与深度，逆 BFS 序回推子树大小与重儿子；
    第二遍沿重链铺剖分下标，轻儿子各开一条新链，同一条链的下标随深度递增。
    """
    start, nb = adj
    par = [0] * (n + 1)
    dep = [0] * (n + 1)
    order = [1]
    for u in order:  # 边遍历边扩容，迭代顺序即 BFS 序
        du = dep[u] + 1
        pu = par[u]
        for j in range(start[u], start[u + 1]):
            v = nb[j]
            if v != pu:
                par[v] = u
                dep[v] = du
                order.append(v)

    siz = [1] * (n + 1)
    siz[0] = 0  # 哨兵：没有重儿子时比大小用
    heavy = [0] * (n + 1)
    for i in range(n - 1, 0, -1):  # 跳过 order[0]=根，其余按逆 BFS 序保证儿子先算完
        u = order[i]
        p = par[u]
        siz[p] += siz[u]
        if siz[u] > siz[heavy[p]]:
            heavy[p] = u

    top = [0] * (n + 1)
    dfn = [0] * (n + 1)
    wd = [0] * n
    cur = 0
    stk = [1]
    stkt = [1]
    while stk:
        u = stk.pop()
        t = stkt.pop()
        while u:
            top[u] = t
            dfn[u] = cur
            wd[cur] = w[u]
            cur += 1
            hv = heavy[u]
            pu = par[u]
            for j in range(start[u], start[u + 1]):
                v = nb[j]
                if v != pu and v != hv:  # 轻儿子各自开一条新链
                    stk.append(v)
                    stkt.append(v)
            u = hv
    return par, dep, top, dfn, wd


def build_seg(wd: list[int], mask: int) -> Seg:
    """按剖分下标建迭代式线段树，每结点存正反两个方向的变换 (F(0^k), F(1^k))。

    单点的 F(x) = ~(x & w) 只取低 k 位，故 F(0) = mask、F(1) = mask ^ w；
    补到 2 的幂的空叶子用恒等变换（F(0) = 0、F(1) = mask），不会干扰区间查询。
    """
    n = len(wd)
    size = 1
    while size < n:
        size <<= 1
    fa = [0] * (2 * size)  # 正向 F(0)：dfs 序递增方向
    fb = [0] * (2 * size)  # 正向 F(1)
    ba = [0] * (2 * size)  # 反向 F(0)：dfs 序递减方向
    bb = [0] * (2 * size)  # 反向 F(1)
    for i in range(size):
        p = size + i
        if i < n:
            fa[p] = ba[p] = mask
            fb[p] = bb[p] = mask ^ wd[i]
        else:
            fa[p] = ba[p] = 0
            fb[p] = bb[p] = mask
    for p in range(size - 1, 0, -1):
        l = p << 1
        r = l | 1
        la = fa[l]
        lb = fb[l]
        ra = fa[r]
        rb = fb[r]
        fa[p] = (la & rb) | (~la & ra)  # 先左后右：F(x) = R(L(x))
        fb[p] = (lb & rb) | (~lb & ra)
        la = ba[l]
        lb = bb[l]
        ra = ba[r]
        rb = bb[r]
        ba[p] = (ra & lb) | (~ra & la)  # 先右后左：G(x) = L(R(x))
        bb[p] = (rb & lb) | (~rb & la)
    return fa, fb, ba, bb, size


def apply_fwd(val: int, lo: int, hi: int, wd: list[int], mask: int, seg: Seg) -> int:
    """把剖分下标区间 [lo, hi] 上的点按下标递增顺序（自顶向下）依次 nand 到 val 上。"""
    if hi - lo <= THRESH:  # 短区间直接扫，比走线段树快
        for i in range(lo, hi + 1):
            val = mask ^ (val & wd[i])
        return val
    fa, fb, _ba, _bb, size = seg
    l = lo + size
    r = hi + size + 1
    pend = []
    while l < r:
        if l & 1:
            val = (~val & fa[l]) | (val & fb[l])
            l += 1
        if r & 1:
            r -= 1
            pend.append(r)  # 右半边结点覆盖的下标更小，留到循环后按序施加
        l >>= 1
        r >>= 1
    for p in reversed(pend):
        val = (~val & fa[p]) | (val & fb[p])
    return val


def apply_bwd(val: int, lo: int, hi: int, wd: list[int], mask: int, seg: Seg) -> int:
    """把剖分下标区间 [lo, hi] 上的点按下标递减顺序（自底向上）依次 nand 到 val 上。"""
    if hi - lo <= THRESH:
        for i in range(hi, lo - 1, -1):
            val = mask ^ (val & wd[i])
        return val
    _fa, _fb, ba, bb, size = seg
    l = lo + size
    r = hi + size + 1
    pend = []
    while l < r:
        if l & 1:
            pend.append(l)  # 左半边结点覆盖的下标更大，留到最后按逆序施加
            l += 1
        if r & 1:
            r -= 1
            val = (~val & ba[r]) | (val & bb[r])
        l >>= 1
        r >>= 1
    for p in reversed(pend):
        val = (~val & ba[p]) | (val & bb[p])
    return val


def path_value(x: int, y: int, mask: int, hld: Hld, seg: Seg) -> int:
    """求 x -> y 路径的折叠结果 f(L)：初始值 0，沿路径逐点 nand。

    路径被 LCA 切成两半：x 侧沿链向上跳，段内下标递减，用反向查询；y 侧自顶向下，
    段内下标递增，用正向查询。x 侧在路径上排在前面，故先施加；y 侧各段是自底向上
    收集到的，要逆序（变成自顶向下）才与路径同向。
    """
    par, dep, top, dfn, wd = hld
    val = 0  # f 的初始值
    pend = []  # lca -> y 一侧的区间，自底向上收集，最后逆序施加
    while top[x] != top[y]:
        if dep[top[x]] >= dep[top[y]]:
            val = apply_bwd(val, dfn[top[x]], dfn[x], wd, mask, seg)
            x = par[top[x]]
        else:
            pend.append((dfn[top[y]], dfn[y]))
            y = par[top[y]]
    if dep[x] >= dep[y]:  # y 就是 lca，整段归 x 侧，lca 不重复计入
        val = apply_bwd(val, dfn[y], dfn[x], wd, mask, seg)
    else:  # x 就是 lca，y 侧还要接上 lca 以下的点
        val = apply_bwd(val, dfn[x], dfn[x], wd, mask, seg)
        pend.append((dfn[x] + 1, dfn[y]))
    for lo, hi in reversed(pend):
        val = apply_fwd(val, lo, hi, wd, mask, seg)
    return val


def set_value(x: int, w: int, mask: int, hld: Hld, seg: Seg) -> None:
    """把结点 x 的点权改成 w，再自底向上重算线段树沿途的结点。"""
    _par, _dep, _top, dfn, wd = hld
    fa, fb, ba, bb, size = seg
    d = dfn[x]
    wd[d] = w
    p = size + d
    fa[p] = ba[p] = mask
    fb[p] = bb[p] = mask ^ w
    p >>= 1
    while p:
        l = p << 1
        r = l | 1
        la = fa[l]
        lb = fb[l]
        ra = fa[r]
        rb = fb[r]
        fa[p] = (la & rb) | (~la & ra)  # 先左后右：F(x) = R(L(x))
        fb[p] = (lb & rb) | (~lb & ra)
        la = ba[l]
        lb = bb[l]
        ra = ba[r]
        rb = bb[r]
        ba[p] = (ra & lb) | (~ra & la)  # 先右后左：G(x) = L(R(x))
        bb[p] = (rb & lb) | (~rb & la)
        p >>= 1


def solve() -> None:
    """读入树与操作序列，逐条处理并输出每个 Query 的答案。"""
    it = iter(sys.stdin.buffer.read().split())
    n = int(next(it))
    m = int(next(it))
    k = int(next(it))
    mask = (1 << k) - 1  # k 可达 32，Python 整数无溢出之虞
    w = [0] * (n + 1)
    for i in range(1, n + 1):
        w[i] = int(next(it))
    eu = [0] * n
    ev = [0] * n
    for e in range(1, n):
        eu[e] = int(next(it))
        ev[e] = int(next(it))

    hld = heavy_light(n, w, build_adj(n, eu, ev))
    seg = build_seg(hld[4], mask)

    out = []
    for _ in range(m):
        op = next(it)
        x = int(next(it))
        if op == b"Query":
            out.append(path_value(x, int(next(it)), mask, hld, seg))
        else:
            set_value(x, int(next(it)) & mask, mask, hld, seg)
    sys.stdout.write("\n".join(map(str, out)) + ("\n" if out else ""))


if __name__ == "__main__":
    solve()
