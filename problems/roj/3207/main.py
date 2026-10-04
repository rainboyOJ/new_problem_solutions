#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:46
# update_at: 2026-10-02 01:51

import re
import sys
from array import array
from collections import deque

BIG = 1 << 20  # "不可割断"的容量：一次最多删 n <= 50 个点，远小于它
HEAD = -1      # 链式前向星的"没有下一条边"


def max_flow(to: list[int], cap: array, nxt: list[int], head: list[int],
             s: int, t: int) -> int:
    """Dinic 最大流：cap 是对称存边（边 e 的反向边是 e ^ 1），head 是出边链头。"""
    size = len(head)
    total = 0
    while True:
        level = [-1] * size                   # BFS 分层：-1 表示本次还没到过
        level[s] = 0
        queue = deque([s])
        while queue:
            u = queue.popleft()
            e = head[u]
            while e != HEAD:
                v = to[e]
                if cap[e] > 0 and level[v] < 0:
                    level[v] = level[u] + 1
                    queue.append(v)
                e = nxt[e]
        if level[t] < 0:                      # 汇点不可达，已无增广路
            return total

        path: list[tuple[int, int]] = []       # DFS 栈，元素是 (点, 从该点走出去的边号)
        u = s
        while True:
            if u == t:
                bottle = min(cap[e] for _, e in path)
                for _, e in path:
                    cap[e] -= bottle
                    cap[e ^ 1] += bottle
                total += bottle
                # 退回到第一条被榨干的边，从那里继续找下一条增广路
                first = next(i for i, (_, e) in enumerate(path) if cap[e] == 0)
                path = path[:first]
                u = to[path[-1][1]] if path else s
            else:
                e, found = head[u], HEAD
                while e != HEAD:
                    v = to[e]
                    if cap[e] > 0 and level[v] == level[u] + 1:
                        found = e
                        break
                    e = nxt[e]
                if found != HEAD:
                    path.append((u, found))
                    u = to[found]
                elif not path:                 # 从源点出发已无路可走
                    break
                else:                          # u 分层内废点：作废它的层号，避免重扫
                    level[u] = -1
                    u = path.pop()[0]


def build_network(n: int, neighbors: list[set[int]]) -> tuple[list[int], list[int],
                                                              list[int], list[int],
                                                              list[int]]:
    """拆点建图：点 v 换成 2v -> 2v+1 的容量 1 弧，原图无向边换成容量 BIG 的双向弧。"""
    to: list[int] = []
    nxt: list[int] = []
    head = [HEAD] * (2 * n)
    split: list[int] = []        # split[v] = 点 v 那条"拆点弧"的边号
    cross: list[int] = []        # cross = 所有表示原图边的弧的边号

    def link(u: int, v: int) -> int:
        """连一条有向弧 u->v，紧跟一条残量 0 的反向弧，返回正向弧的边号。"""
        to.append(v)
        nxt.append(head[u])
        head[u] = len(to) - 1
        to.append(u)
        nxt.append(head[v])
        head[v] = len(to) - 1
        return len(to) - 2

    for v in range(n):
        split.append(link(2 * v, 2 * v + 1))
    for a in range(n):
        for b in neighbors[a]:
            if a < b:                # 无向边只连一次，两个方向各一条弧
                cross += [link(2 * a + 1, 2 * b), link(2 * b + 1, 2 * a)]

    base = [0] * len(to)             # 残量模板：只与源汇无关的部分
    for v in range(n):
        base[split[v]] = 1           # 删一个普通点花 1 的代价
    for e in cross:
        base[e] = BIG                # 原图的边删不掉，等价于无穷容量
    return to, nxt, head, split, base


def vertex_connectivity(n: int, edges: list[tuple[int, int]]) -> int:
    """最少删几个点能让图不连通；删不掉时按题面要求返回 n。"""
    if n == 0:
        return 0
    neighbors = [set() for _ in range(n)]       # 去掉自环与重边，避免无向边容量被重复叠加
    for a, b in edges:
        if a != b:
            neighbors[a].add(b)
            neighbors[b].add(a)

    seen, stack = {0}, [0]                      # 先看原图是否已经断开（孤立点也算断开）
    while stack:
        fresh = neighbors[stack.pop()] - seen
        seen |= fresh
        stack += fresh
    if len(seen) != n:
        return 0

    to, nxt, head, split, base = build_network(n, neighbors)
    best = n      # 删光 n 个点一定不连通，所以答案的上界就是 n（n = 1 时无点对可枚举，正好返回 1）
    for s in range(n):
        for t in range(s + 1, n):
            cap = array("i", base)
            cap[split[s]] = cap[split[t]] = BIG  # 源、汇不许被删
            flow = max_flow(to, cap, nxt, head, 2 * s, 2 * t + 1)
            if flow < best:
                best = flow
                if best <= 1:                    # 已经断开 / 只有割点，不可能更小
                    return best
    return best


def solve() -> None:
    # 抽掉数据文件末尾可能出现的 ^Z；\d+ 会把 (x,y) 与 n、m 一起按出现顺序抽成整数流
    flat = list(map(int, re.findall(rb"\d+", sys.stdin.buffer.read().replace(b"\x1a", b" "))))
    out: list[str] = []
    pos = 0
    while pos + 1 < len(flat):
        n, m = flat[pos], flat[pos + 1]
        edges = list(zip(flat[pos + 2:pos + 2 + 2 * m:2], flat[pos + 3:pos + 3 + 2 * m:2]))
        pos += 2 + 2 * m
        out.append(str(vertex_connectivity(n, edges)))
    print("\n".join(out))


if __name__ == "__main__":
    solve()
