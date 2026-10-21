#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:40
# update_at: 2026-10-21 08:20
#
# main.py：糖果。五类大小关系 + 每人至少一颗，求最小糖果总数。
# 全部写成下界形式 x_v >= x_u + w：
#   X=1 相等     -> 两个方向各一条 0 权边
#   X=2 少于     -> x_b >= x_a + 1（整数性让"少于"就是"至少少 1"）
#   X=3 不少于   -> x_b >= x_a 的反向：x_a >= x_b，权 0
#   X=4 多于     -> x_a >= x_b + 1
#   X=5 不多于   -> x_b >= x_a，权 0
# 要求最少就是求最长路，初值 1（每人至少一颗）。
# 矛盾判定：权值只有 0/1，所以环权和 = 环上权 1 边的条数；而任何有向环都完全落在
# 某个强连通分量内，于是只需检查每个分量内部有没有权 1 边。全 0 环权和为 0，无害。
# 无解排除后缩点成 DAG，按拓扑序做最长路；同分量点强制相等，最后按分量大小加权求和。

import sys
from collections import deque

type Adj = list[list[int]]          # 邻接表，只存终点
type EdgeList = list[tuple[int, int, int]]  # (起点 u, 终点 v, 权 w)，含义 x_v >= x_u + w


def build_graph(n: int, data) -> tuple[Adj, Adj, EdgeList, bool]:
    """返回 (正向图, 反向图, 边表, 是否已判定矛盾)。"""
    graph: Adj = [[] for _ in range(n + 1)]
    reverse_graph: Adj = [[] for _ in range(n + 1)]
    edges: EdgeList = []
    possible = True

    def add_edge(u: int, v: int, w: int) -> None:
        """加一条 u -> v 权 w 的有向边：x_v >= x_u + w。"""
        graph[u].append(v)
        reverse_graph[v].append(u)
        edges.append((u, v, w))

    for _ in range(next(data)):
        kind, a, b = next(data), next(data), next(data)
        if kind == 1:
            add_edge(a, b, 0)   # x_a >= x_b
            add_edge(b, a, 0)   # x_b >= x_a
        elif kind == 2:
            possible &= a != b  # 自己少于自己必矛盾
            add_edge(a, b, 1)   # x_b >= x_a + 1
        elif kind == 3:
            add_edge(b, a, 0)   # x_a >= x_b
        elif kind == 4:
            possible &= a != b  # 自己多于自己必矛盾
            add_edge(b, a, 1)   # x_a >= x_b + 1
        else:
            add_edge(a, b, 0)   # x_a <= x_b 即 x_b >= x_a

    return graph, reverse_graph, edges, possible


def kosaraju(graph: Adj, reverse_graph: Adj, n: int) -> tuple[list[int], int]:
    """两遍 DFS 求强连通分量；返回 (每个点所属分量编号, 分量个数)。

    用显式栈代替递归，避免 n=1e5 的链超出递归深度。
    """
    visited = bytearray(n + 1)
    finish_order: list[int] = []

    # 第一遍：正向图 DFS，记录每个点的结束时间
    for start in range(1, n + 1):
        if visited[start]:
            continue
        visited[start] = 1
        stack = [(start, 0)]  # (点, 下一条要看的出边下标)
        while stack:
            node, index = stack[-1]
            if index < len(graph[node]):
                neighbor = graph[node][index]
                stack[-1] = (node, index + 1)
                if not visited[neighbor]:
                    visited[neighbor] = 1
                    stack.append((neighbor, 0))
            else:
                finish_order.append(node)
                stack.pop()

    # 第二遍：按结束时间逆序在反向图上 DFS，一个连通块就是一个分量
    component = [0] * (n + 1)
    component_count = 0
    for start in reversed(finish_order):
        if component[start]:
            continue
        component_count += 1
        component[start] = component_count
        stack = [start]
        while stack:
            node = stack.pop()
            for neighbor in reverse_graph[node]:
                if component[neighbor] == 0:
                    component[neighbor] = component_count
                    stack.append(neighbor)

    return component, component_count


def contract(
    edges: EdgeList, component: list[int], component_count: int, n: int
) -> tuple[list[list[tuple[int, int]]], list[int], list[int], bool]:
    """缩点：返回 (分量 DAG, 入度, 分量大小, 是否无正环)。

    同一分量内出现权 1 边就是正环（要求 x > x），直接判无解。
    """
    size = [0] * (component_count + 1)
    for node in range(1, n + 1):
        size[component[node]] += 1

    dag: list[list[tuple[int, int]]] = [[] for _ in range(component_count + 1)]
    indegree = [0] * (component_count + 1)
    for u, v, w in edges:
        source, target = component[u], component[v]
        if source == target:
            if w:
                return dag, indegree, size, False  # 分量内权 1 边 = 正环
        else:
            dag[source].append((target, w))
            indegree[target] += 1

    return dag, indegree, size, True


def longest_path_in_dag(
    dag: list[list[tuple[int, int]]], indegree: list[int], component_count: int
) -> list[int]:
    """按拓扑序求每个分量的最长路值，初值全 1（每人至少一颗）。"""
    value = [1] * (component_count + 1)
    queue = deque(node for node in range(1, component_count + 1) if indegree[node] == 0)

    while queue:
        node = queue.popleft()
        for neighbor, weight in dag[node]:
            candidate = value[node] + weight
            if candidate > value[neighbor]:
                value[neighbor] = candidate
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    return value


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    graph, reverse_graph, edges, possible = build_graph(n, data)
    if not possible:
        print(-1)  # 自环形式的显式矛盾
        return

    component, component_count = kosaraju(graph, reverse_graph, n)
    dag, indegree, size, possible = contract(edges, component, component_count, n)
    if not possible:
        print(-1)  # 分量内有权 1 边，正环无解
        return

    value = longest_path_in_dag(dag, indegree, component_count)
    print(sum(value[c] * size[c] for c in range(1, component_count + 1)))


if __name__ == "__main__":
    solve()
