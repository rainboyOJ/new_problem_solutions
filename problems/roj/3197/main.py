#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:09
# update_at: 2026-10-02 01:09

import sys
from collections.abc import Iterator


def read_graph(n: int, nums: Iterator[int]) -> list[list[int]]:
    """按题面格式读出邻接表：每所学校的名单以 0 结束，只有一个 0 表示空名单。"""
    graph: list[list[int]] = []
    for _ in range(n):
        cur: list[int] = []
        while (x := next(nums)):        # 0 是名单结束符，0 之前的都是被支援的学校
            cur.append(x - 1)           # 题面点号从 1 开始，统一转成 0 开始
        graph.append(cur)
    return graph


def finish_order(graph: list[list[int]]) -> list[int]:
    """第一遍 DFS（迭代版）：返回全部点，按「完成时间」从早到晚排列（越晚完成越靠后）。"""
    seen = [False] * len(graph)
    order: list[int] = []
    for root in range(len(graph)):
        if seen[root]:
            continue
        seen[root] = True
        stack = [(root, 0)]             # (点, 下一条待走出去的边的下标)
        while stack:
            v, i = stack[-1]
            if i == len(graph[v]):      # 出边走完，此刻 v 的完成时间最晚
                order.append(v)
                stack.pop()
                continue
            stack[-1] = (v, i + 1)      # 先记下"这条边用过了"，再决定是否递归下去
            if not seen[u := graph[v][i]]:
                seen[u] = True
                stack.append((u, 0))
    return order


def component_of(graph: list[list[int]], order: list[int]) -> list[int]:
    """第二遍在反图上按完成时间逆序 DFS，得到每点所属强连通分量（用分量内代表点编号）。"""
    reverse = [[] for _ in graph]
    for v, nbrs in enumerate(graph):
        for u in nbrs:
            reverse[u].append(v)

    comp = [-1] * len(graph)
    for start in reversed(order):
        if comp[start] != -1:
            continue
        comp[start] = start             # 分量编号取该分量里完成最晚的点，天然不重复
        stack = [start]
        while stack:
            for u in reverse[stack.pop()]:
                if comp[u] == -1:
                    comp[u] = start
                    stack.append(u)
    return comp


def condensation_degrees(graph: list[list[int]], comp: list[int]) -> tuple[int, int]:
    """缩点后退化为 DAG，返回入度为 0 的分量数与出度为 0 的分量数。"""
    has_in = {c: False for c in comp}
    has_out = {c: False for c in comp}
    for v, nbrs in enumerate(graph):
        for u in nbrs:
            if comp[v] != comp[u]:      # 分量内部的边缩点后消失，不影响度数
                has_out[comp[v]] = True
                has_in[comp[u]] = True
    return (sum(not has_in[c] for c in has_in), sum(not has_out[c] for c in has_out))


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    n = next(data)

    graph = read_graph(n, data)
    comp = component_of(graph, finish_order(graph))
    sources, sinks = condensation_degrees(graph, comp)

    # 全图只有一个强连通分量时本身已互通，加 0 条边即可；否则把 max(源,汇) 当作答案
    merged = 0 if len(set(comp)) == 1 else max(sources, sinks)
    print(sources, merged, sep='\n')


if __name__ == "__main__":
    solve()
