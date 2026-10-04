#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 14:16
# update_at: 2026-10-02 14:16

import sys
from array import array

INF = 10**18  # 不可行的代价哨兵
BAD = 10**17  # 真实开销上界约 1e10，累计值超过它即判定不可行


def build_tree(n: int, edges: list[tuple[int, int]]) -> tuple[array, array, list[int]]:
    """以 0 号点为根展开无根树，返回每个点的父亲、深度和先根序。"""
    adj: list[list[int]] = [[] for _ in range(n)]
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
    parent = array("i", [-1] * n)
    parent[0] = 0  # 根的父亲指向自己，倍增表越界时自然收敛到根
    depth = array("i", bytes(4 * n))
    order: list[int] = []
    stack = [0]
    while stack:
        u = stack.pop()
        order.append(u)
        for v in adj[u]:
            if parent[v] == -1:
                parent[v] = u
                depth[v] = depth[u] + 1
                stack.append(v)
    return parent, depth, order


def subtree_cost(price: list[int], parent: array, order: list[int]) -> tuple[array, array, array]:
    """自底向上做树形 DP：f0/f1[u] 是 u 不驻军/驻军时子树的最小开销，best 取两者较小。"""
    n = len(price)
    f0 = array("q", bytes(8 * n))
    f1 = array("q", bytes(8 * n))
    best = array("q", bytes(8 * n))
    for i in range(n - 1, -1, -1):  # 先根序倒过来 = 子树先于父亲处理
        u = order[i]
        f1[u] += price[u]  # 驻军要付自己的花费
        best[u] = f0[u] if f0[u] < f1[u] else f1[u]
        if u:  # 把 u 的贡献推给父亲：父亲不驻军则 u 必须驻军，否则 u 自由取小
            p = parent[u]
            f0[p] += f1[u]
            f1[p] += best[u]
    return f0, f1, best


def upper_cost(parent: array, order: list[int], f0: array, f1: array, best: array) -> tuple[array, array]:
    """自顶向下换根：top0/top1[u] = 除 u 的子树外整棵树的最小开销（u 状态 0/1）。"""
    n = len(parent)
    g0 = array("q", bytes(8 * n))
    g1 = array("q", bytes(8 * n))
    for u in order:
        if not u:
            continue
        p = parent[u]
        stay = g1[p] + f1[p] - best[u]  # 父亲驻军：扣掉 u 子树那份，边由父亲覆盖
        g0[u] = stay  # u 不驻军时边 (p,u) 只能靠父亲，故只保留 stay
        leave = g0[p] + f0[p] - f1[u]  # 父亲不驻军：u 必须驻军，边由 u 覆盖
        g1[u] = leave if leave < stay else stay
    top0 = array("q", (f0[i] + g0[i] for i in range(n)))
    top1 = array("q", (f1[i] + g1[i] for i in range(n)))
    return top0, top1


def jump_tables(parent: array, kmax: int) -> tuple[list, list]:
    """倍增祖先表 anc[k][u]；down[k][u] = u 上方第 2^(k-1)-1 级祖先，供跳步取修正项。"""
    n = len(parent)
    anc = [parent]
    for k in range(1, kmax):
        prev = anc[k - 1]
        anc.append(array("i", (prev[prev[i]] for i in range(n))))
    down: list = [None, array("i", range(n))]  # down[1][u] = u 自身（跳 1 层时正下方就是它）
    for k in range(2, kmax + 1):
        low, up = down[k - 1], anc[k - 2]
        down.append(array("i", (low[up[i]] for i in range(n))))
    return anc, down


def path_matrices(n: int, kmax: int, depth: array, anc: list, down: list,
                  f0: array, f1: array, best: array) -> array:
    """预处理路径倍增矩阵：fmat 压平成 kmax*n*4，每块是 2x2 的 min-plus 矩阵。

    矩阵 (x, y) = 路径 {u, ..., 2^k 祖先的前一个点} 在两端状态 x、y 下的最小开销，
    含路径点的花费与悬挂子树，不含顶端祖先本身。
    """
    fmat = array("q", bytes(32 * n * kmax))  # kmax 层，先全部置 0
    fmat[:4 * n] = array("q", (v for u in range(n) for v in (INF, f0[u], f1[u], f1[u])))  # 0 层
    for k in range(1, kmax):
        prev, cur = (k - 1) * n * 4, k * n * 4
        threshold = 1 << k
        ak, dk = anc[k - 1], down[k]
        for u in range(n):
            if depth[u] < threshold:
                continue  # 深度不够的点没有 2^k 祖先，该块永远读不到
            pu = prev + 4 * u
            a00, a01, a10, a11 = fmat[pu], fmat[pu + 1], fmat[pu + 2], fmat[pu + 3]
            v = ak[u]
            pv = prev + 4 * v
            b00, b01, b10, b11 = fmat[pv], fmat[pv + 1], fmat[pv + 2], fmat[pv + 3]
            w = dk[u]  # 合并处 v 在路径上的孩子：两半都算过它，要扣掉一份
            c0, c1 = f1[w], best[w]
            q = cur + 4 * u
            t, r = a00 + b00 - c0, a01 + b10 - c1
            fmat[q] = t if t < r else r
            t, r = a00 + b01 - c0, a01 + b11 - c1
            fmat[q + 1] = t if t < r else r
            t, r = a10 + b00 - c0, a11 + b10 - c1
            fmat[q + 2] = t if t < r else r
            t, r = a10 + b01 - c0, a11 + b11 - c1
            fmat[q + 3] = t if t < r else r
    return fmat


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())
    n = int(next(tokens))
    m = int(next(tokens))
    _ = next(tokens)  # 官方子任务类型标记，如 "C3"；只决定官方部分分，本解法对任意形态通用
    data = iter(map(int, tokens))
    price = [next(data) for _ in range(n)]
    edges = [(next(data) - 1, next(data) - 1) for _ in range(n - 1)]

    parent, depth, order = build_tree(n, edges)
    f0, f1, best = subtree_cost(price, parent, order)
    top0, top1 = upper_cost(parent, order, f0, f1, best)
    kmax = max(1, max(depth).bit_length())  # 最深点需要的倍增层数
    anc, down = jump_tables(parent, kmax)
    fmat = path_matrices(n, kmax, depth, anc, down, f0, f1, best)

    def climb(k: int, u: int, w: int, s0: int, s1: int) -> tuple[int, int, int, int]:
        """u 上跳 2^k 层：w 是跳之前 u 正下方的路径点（首跳时 w == u）。

        返回新位置、新位置正下方的点、累乘后的矩阵行 (s0, s1)。
        """
        base = 4 * (k * n + u)
        g00, g01, g10, g11 = fmat[base], fmat[base + 1], fmat[base + 2], fmat[base + 3]
        # f 矩阵把 u 整棵子树都记在 u 头上，而 u 下方那段已算进累积行；
        # 只在之前累积过（w != u）时扣掉路径孩子那份，避免重复计算
        c0 = f1[w] if w != u else 0
        c1 = best[w] if w != u else 0
        return (anc[k][u], down[k + 1][u],
                min(s0 + g00 - c0, s1 + g10 - c1), min(s0 + g01 - c0, s1 + g11 - c1))

    def answer(a: int, x: int, b: int, y: int) -> int:
        """强制 a 取状态 x、b 取状态 y 时的最小开销；不可行返回 -1。"""
        la, lb = a, b
        da, db = a, b  # 两端当前位置正下方的路径点，LCA 就是某一端时用它修正
        a0 = 0 if x == 0 else INF  # 单位矩阵的第 x 行：只有状态 x 代价为 0
        a1 = INF if x == 0 else 0
        b0 = 0 if y == 0 else INF
        b1 = INF if y == 0 else 0

        # 第一阶段：把较深的一端逐级抬到同一深度，顺路累乘路径转移矩阵
        if depth[la] != depth[lb]:
            for k in range(kmax - 1, -1, -1):
                step = 1 << k
                if depth[la] - step >= depth[lb]:
                    la, da, a0, a1 = climb(k, la, da, a0, a1)
                elif depth[lb] - step >= depth[la]:
                    lb, db, b0, b1 = climb(k, lb, db, b0, b1)

        # 第二阶段：两端同步上跳到 LCA 正下方（两端的 2^k 祖先不同时才跳）
        if la != lb:
            for k in range(kmax - 1, -1, -1):
                if anc[k][la] != anc[k][lb]:
                    la, da, a0, a1 = climb(k, la, da, a0, a1)
                    lb, db, b0, b1 = climb(k, lb, db, b0, b1)

        if la == lb:
            c = la  # LCA 恰好是被抬上来的那一端
            va0, va1, vb0, vb1 = a0, a1, b0, b1
            wa = da if a != c else -1  # c 的路径孩子（被抬那端正下方），算 c 时要扣掉
            wb = db if b != c else -1
        else:
            c = parent[la]  # 两端分别停在 LCA 的两个儿子上，还差最后一步到 c
            # 两端自己的花费还没算：F 减去朝向路径下方那份悬挂贡献，再补上边约束
            sa0 = a0 + f0[la] - (f1[da] if la != a else 0)
            sa1 = a1 + f1[la] - (best[da] if la != a else 0)
            va0, va1 = sa1, sa0 if sa0 < sa1 else sa1
            sb0 = b0 + f0[lb] - (f1[db] if lb != b else 0)
            sb1 = b1 + f1[lb] - (best[db] if lb != b else 0)
            vb0, vb1 = sb1, sb0 if sb0 < sb1 else sb1
            wa, wb = la, lb

        # c 自身的花费与悬挂子树（扣除两个路径孩子）再加上 c 以上的整棵树
        cut0 = (f1[wa] if wa >= 0 else 0) + (f1[wb] if wb >= 0 else 0)
        cut1 = (best[wa] if wa >= 0 else 0) + (best[wb] if wb >= 0 else 0)
        cost0 = va0 + vb0 + top0[c] - cut0
        cost1 = va1 + vb1 + top1[c] - cut1
        least = cost0 if cost0 < cost1 else cost1
        return -1 if least >= BAD else least

    queries = [(next(data) - 1, next(data), next(data) - 1, next(data)) for _ in range(m)]
    sys.stdout.write("\n".join(str(answer(*q)) for q in queries))


if __name__ == "__main__":
    solve()
