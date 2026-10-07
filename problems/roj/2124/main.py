#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:36
# update_at: 2026-10-08 07:36

import sys
from collections import deque

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type ReverseAdj = list[list[int]]  # 反图邻接表：rev[v] 里是所有原图中指向 v 的点


def max_reachable(n: int, rev: ReverseAdj) -> list[int]:
    """返回 ans[1..n]：ans[v] 是从 v 出发在原图中能到达的最大编号点。

    反图里 u -> v 的边表示"原图中 v 能走到 u"，所以从 u 出发的搜索覆盖到的点 v
    都在原图中能到达 u。按起点编号从大到小串行染色，编号大的起点先动手，
    某点第一次被染色就取该起点的编号。
    """
    ans = [0] * (n + 1)
    for start in range(n, 0, -1):
        if ans[start]:
            continue                 # 已被更大编号的起点覆盖，答案不会再变小
        ans[start] = start           # 每个点至少能到达自己
        queue = deque([start])
        while queue:
            u = queue.popleft()
            for v in rev[u]:
                if not ans[v]:       # 只在首次到达时染色，每个点至多入队一次
                    ans[v] = start
                    queue.append(v)
    return ans


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    data = iter(map(int, tokens))

    n, m = next(data), next(data)
    rev: ReverseAdj = [[] for _ in range(n + 1)]
    for _ in range(m):
        u, v = next(data), next(data)
        rev[v].append(u)             # 反向建边：原图 u -> v 换成反图 v -> u

    print(*max_reachable(n, rev)[1:])


if __name__ == "__main__":
    solve()
