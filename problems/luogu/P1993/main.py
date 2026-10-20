#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:40
# update_at: 2026-10-20 14:35
#
# main.py：小 K 的农场，差分约束的可行性问题——判断三类作物数量关系能否同时满足。
# 把每个农场看成变量 x_i，三类信息统一改写为 x_v <= x_u + w，建边 u -> v 权 w：
#   type 1（a 比 b 至少多 c）：x_a - x_b >= c  <=>  x_b <= x_a - c，建边 a -> b 权 -c
#   type 2（a 比 b 至多多 c）：x_a - x_b <= c  <=>  x_a <= x_b + c，建边 b -> a 权 c
#   type 3（a 与 b 一样多）：x_a = x_b，即 a <= b 且 b <= a，建两个方向的 0 权边
# 所有点距离取 0 并全部入队（等价于 0 权超级源点）跑 SPFA；
# 没有负环说明约束可满足输出 Yes，出现负环说明自相矛盾输出 No。边权有负数，不能用 Dijkstra。

import sys
from collections import deque

input = sys.stdin.buffer.readline
n, constraints = map(int, input().split())

# graph[u]：若干 (终点 v, 边权 w)，代表 x_v <= x_u + w
graph = [[] for _ in range(n + 1)]
for _ in range(constraints):
    operation = list(map(int, input().split()))
    if operation[0] == 1:
        # x_a - x_b >= c  <=>  x_b <= x_a - c
        _, a, b, c = operation
        graph[a].append((b, -c))
    elif operation[0] == 2:
        # x_a - x_b <= c  <=>  x_a <= x_b + c
        _, a, b, c = operation
        graph[b].append((a, c))
    else:
        # x_a == x_b，等价于 a <= b 且 b <= a，两个方向各一条 0 权边
        _, a, b = operation
        graph[a].append((b, 0))
        graph[b].append((a, 0))

distance = [0] * (n + 1)          # 当前差值上界，即一组候选解
edge_count = [0] * (n + 1)        # 当前 distance 对应的路径边数，达到 n 说明绕出了负环
in_queue = bytearray(b"\x01") * (n + 1)   # 全 1：所有点一开始都在队列里
queue = deque(range(1, n + 1))
possible = True

while queue and possible:
    node = queue.popleft()
    in_queue[node] = 0
    for neighbor, weight in graph[node]:
        candidate = distance[node] + weight
        if candidate < distance[neighbor]:
            distance[neighbor] = candidate
            edge_count[neighbor] = edge_count[node] + 1
            if edge_count[neighbor] >= n:
                # 更短的路用了至少 n 条边，必然绕出了一个负环，即约束矛盾
                possible = False
                break
            if not in_queue[neighbor]:
                queue.append(neighbor)
                in_queue[neighbor] = 1

print("Yes" if possible else "No")
