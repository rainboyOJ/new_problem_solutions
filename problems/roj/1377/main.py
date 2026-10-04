#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:43
# update_at: 2026-09-30 07:43

from collections import deque
import sys


def solve() -> None:
    lines = [line.strip() for line in sys.stdin if line.strip()]
    if not lines:
        return
    m, n = map(int, lines[0].split())

    # 同一条线路中，前面的站点都能花 1 次乘车到达后面的站点
    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for line in lines[1 : m + 1]:
        stops = list(map(int, line.split()))
        for i in range(len(stops)):
            for j in range(i + 1, len(stops)):
                adj[stops[i]].append(stops[j])

    # BFS 求从 1 到 n 的最少乘车次数（边权全为 1）
    dist = [-1] * (n + 1)
    dist[1] = 0
    q = deque([1])

    while q:
        u = q.popleft()
        if u == n:
            break
        for v in adj[u]:
            if dist[v] == -1:
                dist[v] = dist[u] + 1
                q.append(v)

    # 乘车次数减 1 即为换乘次数；不可达则输出 NO
    print("NO" if dist[n] == -1 else max(0, dist[n] - 1))


if __name__ == "__main__":
    solve()
