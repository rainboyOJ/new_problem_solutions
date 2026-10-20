#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:40
# update_at: 2026-10-20 09:46

import sys
from collections import deque

type WeightedAdj = list[list[tuple[int, int]]]  # graph[u]：若干 (终点 v, 边权 w)


def find_solution(graph: WeightedAdj, n: int) -> list[int] | None:
    """返回一组满足全部约束的解；约束自相矛盾（有负环）时返回 None。

    所有点距离取 0 并全部入队，等价于加一个到每个点都是 0 权边的超级源点：
    初值只是假定值，整体平移不影响合法性，所以取 0 最省事。
    用路径边数判负环：更短的路走了至少 n 条边，路径上必然绕出了负环。
    """
    dis = [0] * (n + 1)
    path_len = [0] * (n + 1)  # 当前 dis 对应的路径边数
    in_queue = [True] * (n + 1)
    q = deque(range(1, n + 1))

    while q:
        u = q.popleft()
        in_queue[u] = False
        for v, w in graph[u]:
            shorter = dis[u] + w
            if shorter >= dis[v]:
                continue  # 这条边给不出更紧的上界
            dis[v] = shorter
            path_len[v] = path_len[u] + 1
            if path_len[v] >= n:
                return None
            if not in_queue[v]:
                q.append(v)
                in_queue[v] = True

    return dis[1:]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    graph: WeightedAdj = [[] for _ in range(n + 1)]
    for _ in range(m):
        c, c2, y = next(data), next(data), next(data)
        graph[c2].append((c, y))  # x_c - x_c' <= y  <=>  x_c <= x_c' + y，建边 c' -> c 权 y

    ans = find_solution(graph, n)
    print("NO" if ans is None else " ".join(map(str, ans)))


if __name__ == "__main__":
    solve()
