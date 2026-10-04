#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:09
# update_at: 2026-09-30 06:12

import sys
from collections import defaultdict


def euler_path(adj: dict[int, list[tuple[int, int]]], deg: list[int], m: int) -> list[int]:
    """Hierholzer 迭代版：一路贪心走到底，走不动才把点记进路径；出栈顺序即答案。

    每条无向边各占一个编号（两端都能注销它），故 1-2 之间的平行边不会被漏掉。
    邻居按号码倒排后从栈顶取，每次便拿到最小邻居，输出与参考解一致。
    """
    used = [False] * m                              # used[e]：第 e 条边已被走掉
    odd = [v for v in range(1, len(deg)) if deg[v] % 2]
    start = max(odd) if odd else 1                  # 有奇点就从最大奇点出发，否则任取一点
    path: list[int] = []
    stack = [start]
    while stack:
        v = stack[-1]
        while adj[v] and used[adj[v][-1][1]]:       # 栈顶是已走过的边就弹掉
            adj[v].pop()
        if adj[v]:
            w, e = adj[v].pop()                     # 贪心走向还没用过的邻居
            used[e] = True
            stack.append(w)
        else:
            path.append(stack.pop())                # 无路可走，这个点正式落进路径
    return path                                     # 回溯顺序自后向前拼接，无需再反转


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: dict[int, list[tuple[int, int]]] = defaultdict(list)
    deg = [0] * (n + 1)
    for e in range(m):
        a, b = next(data), next(data)
        adj[a].append((b, e))                       # 存 (邻居, 边编号)
        adj[b].append((a, e))
        deg[a] += 1
        deg[b] += 1
    for v in adj:
        adj[v].sort(key=lambda item: -item[0])      # 倒排，使栈顶 pop 出的是最小邻居

    print(' '.join(map(str, euler_path(adj, deg, m))))


if __name__ == "__main__":
    solve()
