#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 01:19
# update_at: 2026-10-08 01:19

import sys

K = 16  # M <= 15 只占二进制低 4 位，于是 dis xor M 的修正只依赖 dis mod 16

# 类型别名：每个点的 16 个余数桶 / 一组整数
type Rows = list[list[int]]
type Ints = list[int]


def rooted_order(adj: list[list[tuple[int, int]]]) -> tuple[Ints, Ints, Ints]:
    """以 1 为根做迭代先序遍历，返回 (先序序列, 父节点, 到父节点的边权)。"""
    n = len(adj) - 1
    parent = [0] * (n + 1)
    pedge = [0] * (n + 1)
    order: Ints = []
    stack = [1]
    seen = [False] * (n + 1)
    seen[1] = True
    while stack:
        u = stack.pop()
        order.append(u)
        for v, w in adj[u]:
            if not seen[v]:
                seen[v] = True
                parent[v] = u
                pedge[v] = w
                stack.append(v)
    return order, parent, pedge


def subtree_dp(order: Ints, parent: Ints, pedge: Ints) -> tuple[Rows, Ints, Ints]:
    """自底向上汇总：返回 (子树余数分布, 子树距离和, 子树大小)。"""
    n = len(parent) - 1
    cnt: Rows = [[0] * K for _ in range(n + 1)]  # cnt[u][r]：子树 u 内到 u 距离 mod 16 == r 的点数
    sub: Ints = [0] * (n + 1)                    # sub[u]：子树 u 内到 u 的距离之和
    size: Ints = [1] * (n + 1)
    for u in range(1, n + 1):
        cnt[u][0] = 1                            # 只有自己，距离 0

    for u in reversed(order[1:]):                # 逆先序：儿子一定先于父亲被汇总
        p = parent[u]
        w = pedge[u]
        e = w % K
        sub[p] += sub[u] + size[u] * w
        size[p] += size[u]
        rot = cnt[u][-e:] + cnt[u][:-e] if e else cnt[u]  # 子树 u 的点到 p 的距离余数整体后移 e
        cnt[p] = [x + y for x, y in zip(cnt[p], rot)]
    return cnt, sub, size


def reroot_dp(order: Ints, parent: Ints, pedge: Ints, cnt: Rows, sub: Ints,
              size: Ints) -> tuple[Rows, Ints]:
    """换根：由父亲的全树信息推出儿子的全树信息，返回 (全树余数分布, 全树距离和)。"""
    n = len(parent) - 1
    dist: Rows = [None] * (n + 1)  # dist[u][r]：全树中到 u 距离 mod 16 == r 的点数
    total: Ints = [0] * (n + 1)    # total[u]：全树所有点到 u 的距离之和
    dist[1] = cnt[1]
    total[1] = sub[1]

    for u in order[1:]:            # 先序：处理 u 时父亲的全树信息已经算好
        p = parent[u]
        w = pedge[u]
        e = w % K
        rot = cnt[u][-e:] + cnt[u][:-e] if e else cnt[u]  # 子树 u 在 p 的余数桶里的贡献
        rest = [x - y for x, y in zip(dist[p], rot)]      # 扣掉子树 u 后，外部点到 p 的分布
        shift = rest[-e:] + rest[:-e] if e else rest      # 外部点到 u 的距离各多走 w
        dist[u] = [x + y for x, y in zip(cnt[u], shift)]
        total[u] = total[p] + (n - 2 * size[u]) * w       # 子树内各减 w，外部各加 w
    return dist, total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        a, b, c = next(data), next(data), next(data)
        adj[a].append((b, c))
        adj[b].append((a, c))

    order, parent, pedge = rooted_order(adj)
    cnt, sub, size = subtree_dp(order, parent, pedge)
    dist, total = reroot_dp(order, parent, pedge, cnt, sub, size)

    delta = [(r ^ m) - r for r in range(K)]  # 把 dis xor M 拆成 dis 加上这个修正量
    out: list[str] = []
    for u in range(1, n + 1):
        d = dist[u]
        # 距离 0 的点就是 u 自己，题面只统计「其他星球」，故在 r == 0 桶里扣掉它
        ans = total[u] + sum(delta[r] * (d[r] - (1 if r == 0 else 0)) for r in range(K))
        out.append(str(ans))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
