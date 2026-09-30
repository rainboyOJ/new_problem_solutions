#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:09
# update_at: 2026-09-30 20:09

import sys

INF = 1 << 60  # 比任何合法经费和大得多，用来表示"这个状态不成立"


def min_guard_cost(n: int, cost: list[int], children: list[list[int]], root: int) -> int:
    """求树上最小权支配集的权值和：每个点要么自己设看守，要么被父亲或儿子看到。

    dp0[u]：u 自己设看守，u 子树全部被看守的最小花费。
    dp1[u]：u 不设看守，但 u 已被它的某个儿子看到，u 子树全部被看守的最小花费。
    dp2[u]：u 不设看守、也没有任何儿子看到 u，此时 u 只能指望父亲来看它，
            子树内（除 u 自己）必须已经全部被看守的最小花费。
    三者互斥且覆盖全部情况，故答案就是根节点上 min(dp0, dp1)（根没有父亲）。
    """
    # 输入已经是有根树的父子关系，按读入顺序展开即得到自顶向下的遍历序，
    # 逆序就是自底向上的转移序，不需要显式 DFS。
    order: list[int] = []
    stack = [root]
    while stack:
        u = stack.pop()
        order.append(u)
        stack += children[u]

    dp0 = [0] * (n + 1)
    dp1 = [0] * (n + 1)
    dp2 = [0] * (n + 1)

    for u in reversed(order):
        dp0[u] = cost[u] + sum(min(dp0[v], dp1[v], dp2[v]) for v in children[u])
        # u 不设看守时，每个儿子 v 都不能指望 u 来看它，所以只能取 dp0[v] / dp1[v]。
        dp2[u] = sum(min(dp0[v], dp1[v]) for v in children[u])
        # 至少有一个儿子设了看守才能让 u 被看到：把其中一个儿子的 dp2 换成 dp0，
        # 代价增量最小的那次替换就是最优选择。
        extra = min(
            (dp0[v] - min(dp0[v], dp1[v]) for v in children[u]),
            default=INF,  # 叶子没有儿子，dp1 不可能成立
        )
        dp1[u] = dp2[u] + extra

    return min(dp0[root], dp1[root])


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    cost = [0] * (n + 1)
    children: list[list[int]] = [[] for _ in range(n + 1)]
    has_parent = [False] * (n + 1)

    for _ in range(n):
        u, k, m = next(data), next(data), next(data)  # 结点标号、经费、儿子数
        cost[u] = k
        children[u] = [next(data) for _ in range(m)]
        for v in children[u]:
            has_parent[v] = True

    # 题面给出的是"父亲 → 儿子"的有向描述，入度为 0 的结点就是皇宫的起点（根）。
    root = next(u for u in range(1, n + 1) if not has_parent[u])
    print(min_guard_cost(n, cost, children, root))


if __name__ == "__main__":
    solve()
