#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 16:01
# update_at: 2026-10-07 16:01

import sys

MASK = (1 << 64) - 1          # 所有哈希都在 64 位无符号内回绕，等价于 C++ 的 unsigned long long
GOLDEN = 0x9e3779b97f4a7c15   # splitmix64 的加性常数，先加它再混淆才不会丢掉输入的差异

type Graph = list[list[int]]        # 邻接表：下标是点编号，值是该点的邻居列表
type IntArrays = tuple[list[int], list[int]]  # 两个等长整型数组的配对（父亲/先序、子树大小/子树哈希等）


def mix(x: int) -> int:
    """splitmix64 收尾混淆：可逆地把整数打散成雪崩良好的 64 位伪随机值。"""
    x = (x + GOLDEN) & MASK
    x = ((x ^ (x >> 30)) * 0xbf58476d1ce4e5b9) & MASK
    x = ((x ^ (x >> 27)) * 0x94d049bb133111eb) & MASK
    return x ^ (x >> 31)


def rooted_order(g: Graph, root: int) -> IntArrays:
    """迭代 DFS，返回 (par, order)：order 是先序，每个点的父亲都排在它前面。"""
    par = [0] * len(g)
    order: list[int] = []
    stk = [root]
    while stk:
        u = stk.pop()
        order.append(u)
        for v in g[u]:
            if v == par[u]:
                continue          # 树上只有父亲这一个邻居已经走过
            par[v] = u
            stk.append(v)
    return par, order


def subtree_hash(g: Graph, par: list[int], order: list[int]) -> IntArrays:
    """自底向上求子树大小 sz 与子树哈希 f[u] = mix(sz[u]) + Σ mix(f[孩子])。"""
    sz = [1] * len(g)
    f = [0] * len(g)
    for u in reversed(order):
        for v in g[u]:
            if v != par[u]:
                sz[u] += sz[v]
                f[u] += mix(f[v])
        f[u] = (mix(sz[u]) + f[u]) & MASK
    return sz, f


def reroot_hash(g: Graph, par: list[int], order: list[int], sz: list[int], f: list[int]) -> list[int]:
    """换根求 full[u]：整棵树以 u 为根时的哈希；树的点数就是 len(order)。"""
    total = len(order)
    mix_total = mix(total)
    full = [0] * len(g)
    full[order[0]] = f[order[0]]                 # 出发点没有"上方"，full 就是子树哈希
    for u in order:
        for v in g[u]:
            if v == par[u]:
                continue
            # 割掉边 (u, v) 后 u 那一侧（total - sz[v] 个点）：从 full[u] 里摘掉 u 的大小项和 v 的贡献
            up = (mix(total - sz[v]) + full[u] - mix_total - mix(f[v])) & MASK
            full[v] = (mix_total + f[v] - mix(sz[v]) + mix(up)) & MASK
    return full


def best_leaf(g_b: Graph, par_b: list[int], full_b: list[int], f_b: list[int], hash_a: set[int], n: int) -> int:
    """候选叶子里的最小编号：B 的叶子 x 删去后，B - x 的哈希落在 hash_a 里就算合法。"""
    mix_b = mix(n + 1)
    mix_n = mix(n)
    # 删掉叶子 x：它没有孩子（f_b[x] = mix(1)），剩下的 n 个点以它唯一的邻居 par_b[x] 为根
    rest_hash = {x: (full_b[par_b[x]] - mix_b + mix_n - mix(f_b[x])) & MASK
                 for x in range(1, n + 2) if len(g_b[x]) == 1}
    return min(x for x, h in rest_hash.items() if h in hash_a)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    g_a: Graph = [[] for _ in range(n + 1)]      # 树 A：编号 1..n
    for _ in range(n - 1):
        x, y = next(data), next(data)
        g_a[x].append(y)
        g_a[y].append(x)

    g_b: Graph = [[] for _ in range(n + 2)]      # 树 B：编号 1..n+1
    for _ in range(n):
        x, y = next(data), next(data)
        g_b[x].append(y)
        g_b[y].append(x)

    if n == 1:                                   # A 是单点树，B 是一条边，两个叶子都合法
        print(1)
        return

    par_a, order_a = rooted_order(g_a, 1)
    sz_a, f_a = subtree_hash(g_a, par_a, order_a)
    # A 的 n 种根哈希：只要某棵 n 点树与 A 同构，它的哈希必落在这个集合里
    hash_a = set(reroot_hash(g_a, par_a, order_a, sz_a, f_a))

    # B 的根取度数 > 1 的点：否则根自己就是叶子，删掉它的情形会被漏掉（n >= 2 时必存在）
    root_b = next(v for v in range(1, n + 2) if len(g_b[v]) > 1)
    par_b, order_b = rooted_order(g_b, root_b)
    sz_b, f_b = subtree_hash(g_b, par_b, order_b)
    full_b = reroot_hash(g_b, par_b, order_b, sz_b, f_b)

    print(best_leaf(g_b, par_b, full_b, f_b, hash_a, n))


if __name__ == "__main__":
    solve()
