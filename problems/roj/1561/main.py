#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:12
# update_at: 2026-09-30 18:12

import sys


def tour(adj: list[list[int]], root: int) -> tuple[list[int], list[int], list[int]]:
    """迭代 DFS 求欧拉序：返回入点时刻 tin、出点时刻 tout、深度 depth（均为 1 起下标）。

    以入点时刻为编号，子树恰好对应连续区间 [tin[u], tout[u]]。
    """
    n = len(adj) - 1
    tin = [0] * (n + 1)
    tout = [0] * (n + 1)
    depth = [0] * (n + 1)
    t = 0
    stack = [(root, 0, False)]  # (节点, 父节点, 是否为出栈标记)
    while stack:
        u, p, exiting = stack.pop()
        if exiting:
            tout[u] = t  # 此时子树内所有节点都已计完入点时刻
            continue
        t += 1
        tin[u] = t
        depth[u] = depth[p] + 1 if p else 0  # 根深度记 0
        stack.append((u, p, True))
        stack += [(v, u, False) for v in adj[u] if v != p]
    return tin, tout, depth


def bit_add(bit: list[int], i: int, v: int) -> None:
    """树状数组下标 i 加 v。"""
    while i < len(bit):
        bit[i] += v
        i += i & -i


def bit_sum(bit: list[int], i: int) -> int:
    """树状数组前缀和 Σ[1..i]。"""
    s = 0
    while i:
        s += bit[i]
        i -= i & -i
    return s


def range_add(bit: list[int], l: int, r: int, v: int) -> None:
    """区间 [l, r] 每个位置加 v：差分写法，左端 +v、右端后一位 −v，点查即前缀和。"""
    bit_add(bit, l, v)
    bit_add(bit, r + 1, -v)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    weight = [0] + [next(data) for _ in range(n)]

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        fr, to = next(data), next(data)
        adj[fr].append(to)
        adj[to].append(fr)
    tin, tout, depth = tour(adj, 1)

    # 设 A[y] = 根到 y 的路径点权和。每次修改对 A[y] 的贡献要么是常数，
    # 要么是 depth[y] 的线性函数，故拆成两棵树状数组：
    # A[y] = depth[y] * q1 点查 + q2 点查（区间加、点查）。
    q1 = [0] * (n + 2)
    q2 = [0] * (n + 2)

    # 初始权值：u 的权值让子树内每个 y 的路径和都 +weight[u]
    for u in range(1, n + 1):
        range_add(q2, tin[u], tout[u], weight[u])

    out: list[str] = []
    for _ in range(m):
        op = next(data)
        x = next(data)
        l, r = tin[x], tout[x]
        if op == 1:  # 单点加 a：只影响子树内 y 的路径和，统一 +a
            a = next(data)
            range_add(q2, l, r, a)
        elif op == 2:  # 子树加 a：y 的路径和 += a * (子树内祖先个数)
            a = next(data)  # y 在子树内时为 a*(depth[y]-depth[x]+1)，否则为 0
            range_add(q1, l, r, a)                      # depth[y] 的系数 a
            range_add(q2, l, r, a * (1 - depth[x]))     # 常数项 a*(1-depth[x])
        else:  # 询问：根到 x 的路径点权和
            out.append(str(depth[x] * bit_sum(q1, tin[x]) + bit_sum(q2, tin[x])))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
