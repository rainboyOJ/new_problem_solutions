#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-10 08:06
# update_at: 2026-10-10 08:30

import sys


def mark_green(n: int, adj: list[list[int]], is_red: list[int], l: int, r: int) -> list[int]:
    """用多源 BFS 标出到最近红点距离位于 [l,r] 的绿点。"""
    dist = [-1] * (n + 1)
    queue = [i for i in range(1, n + 1) if is_red[i]]
    for i in queue:
        dist[i] = 0

    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        for v in adj[u]:
            if dist[v] == -1:
                dist[v] = dist[u] + 1
                queue.append(v)

    return [0] + [1 if l <= dist[i] <= r else 0 for i in range(1, n + 1)]


def tree_order(n: int, adj: list[list[int]]) -> tuple[list[int], list[int]]:
    """从 1 号点出发得到父亲数组和遍历序，用来迭代换根。"""
    parent = [0] * (n + 1)
    order: list[int] = []
    queue = [1]
    seen = [False] * (n + 1)
    seen[1] = True

    head = 0
    while head < len(queue):
        u = queue[head]
        head += 1
        order.append(u)
        for v in adj[u]:
            if not seen[v]:
                seen[v] = True
                parent[v] = u
                queue.append(v)
    return parent, order


def all_answers(n: int, adj: list[list[int]], is_red: list[int], is_green: list[int]) -> list[int]:
    """换根计算每个询问点收到的红点平方距离和与绿点距离和。"""
    parent, order = tree_order(n, adj)
    red_count = [0] * (n + 1)
    green_count = [0] * (n + 1)
    red_dist = [0] * (n + 1)
    red_dist2 = [0] * (n + 1)
    green_dist = [0] * (n + 1)

    for u in reversed(order):
        red_count[u] = is_red[u]
        green_count[u] = is_green[u]
        for v in adj[u]:
            if v == parent[u]:
                continue
            red_count[u] += red_count[v]
            green_count[u] += green_count[v]
            red_dist[u] += red_dist[v] + red_count[v]
            red_dist2[u] += red_dist2[v] + 2 * red_dist[v] + red_count[v]
            green_dist[u] += green_dist[v] + green_count[v]

    total_red = red_count[1]
    total_green = green_count[1]
    for u in order:
        for v in adj[u]:
            if v == parent[u]:
                continue
            outside_red = total_red - red_count[v]
            outside_red_dist = red_dist[u] - red_dist[v] - red_count[v]
            outside_red_dist2 = red_dist2[u] - red_dist2[v] - 2 * red_dist[v] - red_count[v]
            red_dist[v] += outside_red_dist + outside_red
            red_dist2[v] += outside_red_dist2 + 2 * outside_red_dist + outside_red

            outside_green = total_green - green_count[v]
            outside_green_dist = green_dist[u] - green_dist[v] - green_count[v]
            green_dist[v] += outside_green_dist + outside_green

    return [red_dist2[i] + green_dist[i] for i in range(n + 1)]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n, m, k, l, r = next(data), next(data), next(data), next(data), next(data)
    except StopIteration:
        return

    adj = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = next(data), next(data)
        adj[u].append(v)
        adj[v].append(u)

    is_red = [0] * (n + 1)
    for _ in range(m):
        is_red[next(data)] = 1

    queries = [next(data) for _ in range(k)]
    is_green = mark_green(n, adj, is_red, l, r)
    ans = all_answers(n, adj, is_red, is_green)
    if queries:  # 无询问时不输出空行（与标准程序逐字节一致）
        sys.stdout.write("\n".join(str(ans[x]) for x in queries) + "\n")


if __name__ == "__main__":
    solve()
