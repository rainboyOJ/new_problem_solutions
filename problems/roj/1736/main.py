#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:30
# update_at: 2026-10-07 20:30

import sys
from array import array
from collections import Counter
from math import isqrt

NO_PARENT = -1  # DFS 树的根没有父亲，用它当「无父亲」哨兵

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type NodeList = list[int]                # 合并点（代表同值的若干个原点）的权值
type Adj = list[list[int]]               # 邻接表：合并点 -> 见证数，见证数 -> 合并点
type Witnesses = list[list[int]]         # 每个合并点的见证数节点编号
type PrimePowers = list[tuple[int, int]] # 一个数的质因数分解：(质数, 指数)
type IdMap = dict[int, int]              # 见证数 -> 它在二部图里的节点编号
type LowInfo = tuple[list[int], list[int], list[int], list[int], list[int], list[int]]  # Tarjan 的 6 张表


def build_spf(limit: int) -> array:
    """筛最小质因子表：spf[x]（若为 0 则视为 x）就是 x 的最小质因子。

    先埃氏筛出 <= sqrt(limit) 的质数，再**按从大到小**拿每个质数整片覆盖自己的倍数，
    于是每个位置最后落地的就是最小质因子；只需 <= sqrt(limit) 的质数，因为合数必有不超过
    sqrt 的质因子。因此 x 是质数（或 x < 2）时 spf[x] 仍是 0，调用方用 `spf[x] or x` 补上。
    用 array('i') 而不是 list，10⁷ 长度下内存从几百 MB 降到 40 MB。
    """
    root = isqrt(limit)
    flag = bytearray([1]) * (root + 1)
    flag[0:2] = b"\x00\x00"
    for i in range(2, isqrt(root) + 1):
        if flag[i]:
            flag[i * i:: i] = bytearray(len(range(i * i, root + 1, i)))
    spf = array('i', bytes(4 * (limit + 1)))
    for p in range(root, 1, -1):
        if flag[p]:
            spf[p:: p] = array('i', [p]) * ((limit - p) // p + 1)
    return spf


def prime_powers(x: int, spf: array) -> PrimePowers:
    """把 x 分解成 (质数, 指数) 列表；每轮至少消掉一个质因子。"""
    factors = []
    while x > 1:
        p = spf[x] or x  # spf 的 0 是哨兵，含义见 build_spf
        e = 0
        while x % p == 0:
            x //= p
            e += 1
        factors.append((p, e))
    return factors


def witnesses_of(factors: PrimePowers) -> list[int]:
    """x 的见证数集合：与 x 共享见证数 <=> gcd(x, y) 是合数。

    见证数取「两个不同质因子的积 pq」（gcd 里有两个不同质数）
    或「质因子的平方 p²」（该质数在 gcd 里出现两次以上）。
    """
    return (
        [p * q for i, (p, _) in enumerate(factors) for q, _ in factors[i + 1:]]  # pq 见证
        + [p * p for p, e in factors if e >= 2]                                  # p² 见证
    )


def compress_points(values: list[int], spf: array) -> tuple[NodeList, Witnesses, int]:
    """把同值的点合并，返回 (各组点数, 各组的见证数编号, 见证数个数)。

    点权 v 是合数时同一值的点两两有边（gcd = v 是合数），删掉其中一个既不会切分
    连通块、也不影响别的点，所以它们合成一个权值 = 点数的节点；点权是质数时同一值
    的点两两没边，只能各自留一个权值 1 的节点。度为 1 的见证数只连着唯一一个点，
    永远不影响连通性，一并剪掉。两处都只是把图压小，算法完全不变。
    """
    degree: IdMap = {}             # 见证数 -> 包含它的点（合并后）个数
    weights: NodeList = []
    grouped: Witnesses = []        # 合并后每个点的见证数列表（未剪枝）
    for value, group in Counter(values).items():
        ws = witnesses_of(prime_powers(value, spf))
        # ws 非空 <=> v 是合数 <=> 同值的 group 个点是一个团，可合并成一个权值 group 的点
        weights += [group] if ws else [1] * group
        grouped += [ws] if ws else [[] for _ in range(group)]
        for d in ws:
            degree[d] = degree.get(d, 0) + 1

    base = len(weights)            # 见证数节点编号排在所有合并点之后
    ids: IdMap = {}
    kept: Witnesses = []
    for ws in grouped:
        row: list[int] = []
        for d in ws:
            if degree[d] < 2:      # 只被一个点独占的见证数不影响连通性，剪掉
                continue
            if d not in ids:
                ids[d] = base + len(ids)  # 第一次见到就发一个节点编号
            row.append(ids[d])
        kept.append(row)
    return weights, kept, len(ids)


def build_adj(weights: NodeList, wit: Witnesses) -> Adj:
    """把「合并点 + 见证数」二部图展开成双向邻接表。"""
    adj: Adj = [[] for _ in range(len(weights) + sum(map(len, wit)))]
    for j, row in enumerate(wit):
        adj[j] = row               # 合并点只连自己的见证数
        for d in row:
            adj[d].append(j)       # 见证数连回它的合并点
    return adj


def lowlink(adj: Adj, point_weight: NodeList) -> LowInfo:
    """迭代 Tarjan：返回 (dfn, low, 子树点数, 连通块号, 连通块点数表, 父亲)。

    子树点数只统计合并点（见证数不计入），连通块点数表从下标 1 起给连通块编号。
    """
    nodes = len(adj)
    m = len(point_weight)
    disc = [0] * nodes
    low = [0] * nodes
    par = [NO_PARENT] * nodes
    sub = [0] * nodes      # 子树里的合并点数
    comp = [0] * nodes
    comp_total = [0]       # comp_total[c] 是连通块 c 的合并点总数
    step = [0] * nodes     # 每个节点下一条待遍历的邻边位置
    timer = 0

    for s in range(nodes):
        if disc[s]:
            continue
        cid = len(comp_total)
        timer += 1
        disc[s] = low[s] = timer
        par[s] = NO_PARENT
        sub[s] = point_weight[s] if s < m else 0
        comp[s] = cid
        total = sub[s]
        stack = [s]
        while stack:
            v = stack[-1]
            if step[v] < len(adj[v]):
                u = adj[v][step[v]]
                step[v] += 1
                if u == par[v]:
                    continue                       # 不回走 DFS 树上的父边
                if disc[u] == 0:
                    timer += 1
                    disc[u] = low[u] = timer
                    par[u] = v
                    sub[u] = point_weight[u] if u < m else 0
                    comp[u] = cid
                    total += sub[u]
                    stack.append(u)
                elif disc[u] < low[v]:
                    low[v] = disc[u]               # 回边：low 取 dfn 更小的那个
            else:
                stack.pop()
                p = par[v]
                if p != NO_PARENT:
                    if low[v] < low[p]:
                        low[p] = low[v]
                    sub[p] += sub[v]
        comp_total.append(total)
    return disc, low, sub, comp, comp_total, par


def smallest_after_removal(weights: NodeList, wit: Witnesses) -> int:
    """一组数据的答案：删掉一个点后最大连通块的最小可能值。

    对每个合并点 x：权值 >= 2 的组删一个点不会切分连通块，只是该块少一个点；
    权值 == 1 的组等于删掉这个节点，要用 low/cut 判定被切出去的最大子树。
    """
    adj = build_adj(weights, wit)
    disc, low, sub, comp, comp_total, par = lowlink(adj, weights)
    m = len(weights)

    # 各连通块点数的最大 / 次大 / 最大者个数（并列最大时「其他连通块」仍是最大者）
    top1 = top2 = ties = 0
    for total in comp_total[1:]:
        if total > top1:
            top2, top1, ties = top1, total, 1
        elif total == top1:
            ties += 1
        elif total > top2:
            top2 = total

    best = sum(weights) - 1                # 答案上界：删一个点后至多剩 n-1 个点
    for x in range(m):
        total = comp_total[comp[x]]
        other = top2 if (total == top1 and ties == 1) else top1
        if weights[x] > 1:
            cur = max(total - 1, other)    # 组里少一个点，连通块不被切分
        else:
            cut_max = 0
            rest = total - 1               # 去掉 x 与被切出的各子树后剩下的主体
            for u in adj[x]:
                is_cut_off = par[u] == x and low[u] >= disc[x]  # 这个儿子被 x 切出去了
                if is_cut_off:
                    if sub[u] > cut_max:
                        cut_max = sub[u]
                    rest -= sub[u]
            cur = max(cut_max, rest, other)
        if cur < best:
            best = cur
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    T = next(data)
    tests = []
    max_value = 2
    for _ in range(T):
        n = next(data)
        values = [next(data) for _ in range(n)]
        tests.append(values)
        max_value = max(max_value, max(values))

    spf = build_spf(max_value)             # 全题共用一张最小质因子表
    out = []
    for values in tests:
        weights, wit, _ = compress_points(values, spf)
        out.append(str(smallest_after_removal(weights, wit)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
