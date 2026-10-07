#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:36
# update_at: 2026-10-08 06:36

import sys

type Adj = list[list[int]]  # 邻接表：adj[u] 存 u 的全部邻居（父点 + 儿子）
type Pair = tuple[int, int]  # 评价二元组 (Bob, -Alice)：定义只此一处；Alice 取最小、Bob 取最大


def build_order(root: int, adj: Adj) -> tuple[list[int], list[int]]:
    """返回 (BFS 序, 每个点的父结点)。迭代实现，链长 1e5 也不会爆栈。

    order 自己当队列：边遍历边追加队尾，于是父结点恒排在儿子之前；
    只跳过连回父结点的边（树不会有别的重边）。
    """
    par = [0] * len(adj)
    order = [root]
    for u in order:
        for v in adj[u]:
            if v != par[u]:
                par[v] = u
                order.append(v)
    return order, par


def play(root: int, order: list[int], par: list[int], adj: Adj, num: list[int]) -> Pair:
    """在树上做极小极大 DP，返回 (Alice 总得分, Bob 总得分)。

    谁取结点 u 只由深度决定：根为第 0 层，偶数层 Alice 取、奇数层 Bob 取；
    取完 u 之后由对手从 u 的儿子里挑一个继续。
    """
    dep = [0] * len(adj)  # 到根的深度
    for u in order[1:]:
        dep[u] = dep[par[u]] + 1

    alice = [0] * len(adj)  # 子树内 Alice 的得分（双方均最优）
    bob = [0] * len(adj)    # 子树内 Bob 的得分（双方均最优）

    def pair(v: int) -> Pair:
        """结点 v 的评价二元组，供 max/min 择优使用。"""
        return bob[v], -alice[v]

    for u in reversed(order):  # 逆 BFS 序：儿子先算完
        kids = [v for v in adj[u] if v != par[u]]
        if not kids:  # 叶子：谁取走谁得 num[u]
            if dep[u] % 2 == 0:
                alice[u] = num[u]
            else:
                bob[u] = num[u]
        elif dep[u] % 2 == 0:
            # Alice 取走 num[u]，随后 Bob 挑儿子：让自己多、进而让 Alice 少
            v = max(kids, key=pair)
            alice[u], bob[u] = num[u] + alice[v], bob[v]
        else:
            # Bob 取走 num[u]，随后 Alice 挑儿子：让 Bob 少、进而让自己多
            v = min(kids, key=pair)
            alice[u], bob[u] = alice[v], num[u] + bob[v]

    return alice[root], bob[root]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    num = [0] + [next(data) for _ in range(n)]

    adj: Adj = [[] for _ in range(n + 1)]
    indeg = [0] * (n + 1)  # 入度：有向树上只有根入度为 0，它就是 Alice 先取的那一点
    for _ in range(n - 1):
        u, v = next(data), next(data)
        adj[u].append(v)
        adj[v].append(u)
        indeg[v] += 1
    root = indeg.index(0, 1)  # 从下标 1 开始找第一个入度为 0 的点

    order, par = build_order(root, adj)

    print(*play(root, order, par, adj, num))


if __name__ == "__main__":
    solve()
