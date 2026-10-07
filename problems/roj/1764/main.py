#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 23:31
# update_at: 2026-10-07 23:31

import sys
from collections.abc import Iterator

type IntList = list[int]              # 下标 -> 整数，线段树 / 树链剖分 / 前缀量都用它
type Vec = list[list[int]]            # 邻接表：点 -> 邻居列表


def build_hld(adj: Vec, n: int) -> tuple[IntList, IntList, IntList, IntList, IntList]:
    """树链剖分，返回 (fa, dep, son, top, dfn)，复杂度 O(n)。

    每条重链在 dfn 上连续，于是树上任意一条路径都能拆成 O(log n) 段连续 dfn 区间；
    段内「从 u 数第几个点」这个编号随 dfn 单调，正好是本线段树要处理的形状。
    """
    fa = [0] * (n + 1)
    dep = [0] * (n + 1)
    sz = [0] + [1] * n                # sz[0] = 0 当"没有孩子"的哨兵，其余每个点先算自己
    son = [0] * (n + 1)
    order = [1]                       # 边遍历边追加，天然得到 BFS 序
    for u in order:
        for v in adj[u]:
            if v != fa[u]:
                fa[v] = u
                dep[v] = dep[u] + 1
                order.append(v)
    for u in reversed(order):         # 逆 BFS 序 = 先儿子后父亲
        for v in adj[u]:
            if v != fa[u]:
                sz[u] += sz[v]
                if sz[v] > sz[son[u]]:
                    son[u] = v
    top = [0] * (n + 1)
    dfn = [0] * (n + 1)
    top[1] = 1
    cur = 0
    stk = [1]
    while stk:
        u = stk.pop()
        cur += 1
        dfn[u] = cur
        h = son[u]
        for v in adj[u]:              # 轻儿子先压栈、重儿子后压，于是重儿子先出栈
            if v != fa[u] and v != h:
                top[v] = v
                stk.append(v)
        if h:
            top[h] = top[u]
            stk.append(h)
    return fa, dep, son, top, dfn


def process(n: int, q: int, P: int, adj: Vec, init: IntList, data: Iterator[int]) -> IntList:
    """建树链剖分 + 线段树，顺序执行 q 条操作，返回所有询问的答案（已模 P）。

    线段树上的函数族 f(p) = A*2^(p-lv) + B*2^(rv-p) + C + D*p（lv/rv 是节点 v 的两端）：
    等差部分就是 C + D*p；等比部分把系数锚在区间两端，指数永远非负，
    所以 P 为偶数（2 没有逆元）时照样成立。求和用 2^len-1 与位置和公式，全程不除法。
    """
    fa, dep, son, top, dfn = build_hld(adj, n)

    log = max(1, (n - 1).bit_length())    # size = 2^log ≥ n：叶下标 size+p-1 对应位置 p
    size = 1 << log
    m = 2 * size
    pow2 = [1 % P] * (size + 1)           # pow2[k] = 2^k mod P
    for i in range(1, size + 1):
        pow2[i] = pow2[i - 1] * 2 % P

    ln = [0] * m                          # ln[v]: 节点 v 覆盖的长度
    off = [0] * m                         # off[v]: v 的区间左端在 [0, size) 里的偏移
    ln[1] = size
    for v in range(1, size):
        half = ln[v] >> 1
        ln[v + v] = ln[v + v + 1] = half
        off[v + v] = off[v]
        off[v + v + 1] = off[v] + half
    glen = [0] * m                        # glen[v]: (2^ln[v] - 1) mod P，等比部分的系数
    lenm = [0] * m                        # lenm[v]: ln[v] mod P，常数部分的系数
    sump = [0] * m                        # sump[v]: 区间内位置之和 mod P，一次项系数
    for v in range(1, m):
        d = ln[v]
        glen[v] = (pow2[d] - 1) % P
        lenm[v] = d % P
        sump[v] = ((off[v] + 1 + off[v] + d) * d // 2) % P

    seg = [0] * m                         # 区间和
    tA = [0] * m                          # 懒标记：2^(p-lv) 的系数
    tB = [0] * m                          # 懒标记：2^(rv-p) 的系数
    tC = [0] * m                          # 懒标记：常数项
    tD = [0] * m                          # 懒标记：p 的系数
    isSet = bytearray(m)                  # 1 表示该标记是"整体赋值"而不是"加"
    for i in range(1, n + 1):             # 叶子上放初值
        seg[size + dfn[i] - 1] = init[i - 1] % P
    for v in range(size - 1, 0, -1):
        seg[v] = (seg[v + v] + seg[v + v + 1]) % P

    def push(v: int) -> None:
        """把 v 的懒标记下传：锚点从 v 的两端平移到两个孩子的两端。"""
        A, B, C, D = tA[v], tB[v], tC[v], tD[v]
        w = pow2[ln[v] >> 1]              # 半段长度：右孩子的左锚、左孩子的右锚各差它
        bl, ar = B * w % P, A * w % P
        for c, ca, cb in ((v + v, A, bl), (v + v + 1, ar, B)):
            if isSet[v]:
                seg[c] = ((ca + cb) * glen[c] + C * lenm[c] + D * sump[c]) % P
                tA[c] = ca
                tB[c] = cb
                tC[c] = C
                tD[c] = D
                isSet[c] = 1
            else:
                seg[c] = (seg[c] + (ca + cb) * glen[c] + C * lenm[c] + D * sump[c]) % P
                tA[c] = (tA[c] + ca) % P
                tB[c] = (tB[c] + cb) % P
                tC[c] = (tC[c] + C) % P
                tD[c] = (tD[c] + D) % P
        isSet[v] = 0
        tA[v] = tB[v] = tC[v] = tD[v] = 0

    def apply_node(v: int, A: int, B: int, C: int, D: int, st: int, l0: int, r0: int) -> None:
        """把以查询区间两端为锚的 (A, B) 平移到节点 v 自己的两端，再落到 v 上。"""
        av = A * pow2[off[v] - l0 + size] % P                 # 左锚从 ql 挪到 v 的左端
        bv = B * pow2[r0 - size - off[v] - ln[v]] % P         # 右锚从 qr 挪到 v 的右端
        if st:
            seg[v] = ((av + bv) * glen[v] + C * lenm[v] + D * sump[v]) % P
            tA[v] = av
            tB[v] = bv
            tC[v] = C
            tD[v] = D
            isSet[v] = 1
        else:
            seg[v] = (seg[v] + (av + bv) * glen[v] + C * lenm[v] + D * sump[v]) % P
            tA[v] = (tA[v] + av) % P
            tB[v] = (tB[v] + bv) % P
            tC[v] = (tC[v] + C) % P
            tD[v] = (tD[v] + D) % P

    def range_apply(l: int, r: int, A: int, B: int, C: int, D: int, st: int) -> None:
        """dfn 闭区间 [l, r] 上整体加（st=0）或整体改（st=1）这个函数。"""
        l += size - 1
        r += size                                       # 换成叶下标上的半开区间 [l, r)
        l0, r0 = l, r
        for i in range(log, 0, -1):                     # 先自顶向下把沿途标记推掉
            v = l >> i
            if v << i != l and (isSet[v] or tA[v] or tB[v] or tC[v] or tD[v]):
                push(v)
            if (r >> i) << i != r:
                v = (r - 1) >> i
                if isSet[v] or tA[v] or tB[v] or tC[v] or tD[v]:
                    push(v)
        while l < r:                                    # 覆盖区间的 O(log n) 个节点
            if l & 1:
                apply_node(l, A, B, C, D, st, l0, r0)
                l += 1
            if r & 1:
                r -= 1
                apply_node(r, A, B, C, D, st, l0, r0)
            l >>= 1
            r >>= 1
        l, r = l0, r0
        for i in range(1, log + 1):                     # 自底向上把沿途和重算
            v = l >> i
            if v << i != l:
                seg[v] = (seg[v + v] + seg[v + v + 1]) % P
            if (r >> i) << i != r:
                v = (r - 1) >> i
                seg[v] = (seg[v + v] + seg[v + v + 1]) % P

    def range_sum(l: int, r: int) -> int:
        """dfn 闭区间 [l, r] 上的金币和 mod P。"""
        l += size - 1
        r += size
        for i in range(log, 0, -1):
            v = l >> i
            if v << i != l and (isSet[v] or tA[v] or tB[v] or tC[v] or tD[v]):
                push(v)
            if (r >> i) << i != r:
                v = (r - 1) >> i
                if isSet[v] or tA[v] or tB[v] or tC[v] or tD[v]:
                    push(v)
        res = 0
        while l < r:
            if l & 1:
                res += seg[l]
                l += 1
            if r & 1:
                r -= 1
                res += seg[r]
            l >>= 1
            r >>= 1
        return res % P

    def lca(u: int, v: int) -> int:
        """轻重链跳法求最近公共祖先。"""
        while top[u] != top[v]:
            if dep[top[u]] < dep[top[v]]:
                u, v = v, u
            u = fa[top[u]]
        return u if dep[u] < dep[v] else v

    def seg_apply(l: int, r: int, idx: int, left: int, op: int, a: int, d: int) -> None:
        """段 [l, r] 上施加 op；idx 是锚点处的路径编号，left=1 表示编号随 dfn 递增。"""
        if op == 1 or op == 3:                          # 第 i 个点加/改成 a + (i-1)d
            if left:
                C = (a + (idx - l - 1) % P * d) % P     # i-1 = idx-1 + (p-l)
                D = d
            else:
                C = (a + (idx + r - 1) % P * d) % P     # i-1 = idx-1 + (r-p)
                D = (P - d) % P
            range_apply(l, r, 0, 0, C, D, op == 3)
        else:                                           # 第 i 个点加/改成 a*2^(i-1)
            base = a * pow2[idx - 1] % P                # 锚点处是 a*2^(idx-1)
            range_apply(l, r, base if left else 0, 0 if left else base, 0, 0, op == 4)

    def path_apply(u: int, v: int, op: int, a: int, d: int) -> None:
        """把 u 到 v 路径上的点按从 u 起的顺序编号，施加一次 op 操作。"""
        L = lca(u, v)
        du = dep[u]
        x = u
        while top[x] != top[L]:                         # u 侧：编号 = du-dep[x]+1，随 dfn 递减
            seg_apply(dfn[top[x]], dfn[x], du - dep[x] + 1, 0, op, a, d)
            x = fa[top[x]]
        if x != L:
            seg_apply(dfn[L] + 1, dfn[x], du - dep[x] + 1, 0, op, a, d)
        y = v
        while top[y] != top[L]:                         # v 侧：编号 = du+dep[y]-2dep[L]+1，递增
            seg_apply(dfn[top[y]], dfn[y], du + dep[top[y]] - 2 * dep[L] + 1, 1, op, a, d)
            y = fa[top[y]]
        if y != L:
            seg_apply(dfn[L] + 1, dfn[y], du - dep[L] + 2, 1, op, a, d)
        seg_apply(dfn[L], dfn[L], du - dep[L] + 1, 1, op, a, d)   # L 自己只算一次

    def path_sum(u: int, v: int) -> int:
        """u 到 v 路径上的金币和 mod P。"""
        L = lca(u, v)
        res = 0
        x = u
        while top[x] != top[L]:
            res += range_sum(dfn[top[x]], dfn[x])
            x = fa[top[x]]
        if x != L:
            res += range_sum(dfn[L] + 1, dfn[x])
        y = v
        while top[y] != top[L]:
            res += range_sum(dfn[top[y]], dfn[y])
            y = fa[top[y]]
        if y != L:
            res += range_sum(dfn[L] + 1, dfn[y])
        res += range_sum(dfn[L], dfn[L])
        return res % P

    ans: IntList = []
    for _ in range(q):
        op, u, v = next(data), next(data), next(data)
        if op == 5:
            ans.append(path_sum(u, v))
        elif op == 1 or op == 3:
            path_apply(u, v, op, next(data), next(data))
        else:
            path_apply(u, v, op, next(data), 0)
    return ans


def solve() -> None:
    """读入 + 调用 + 输出。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, q, P = next(data), next(data), next(data)

    adj: Vec = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = next(data), next(data)
        adj[u].append(v)
        adj[v].append(u)
    init = [next(data) for _ in range(n)]      # A_1 .. A_n

    ans = process(n, q, P, adj, init, data)
    sys.stdout.write('\n'.join(map(str, ans)) + ('\n' if ans else ''))


if __name__ == "__main__":
    solve()
