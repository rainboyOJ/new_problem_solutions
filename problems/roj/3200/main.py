#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 01:20
# update_at: 2026-10-02 01:37

import sys
from collections import deque
from collections.abc import Iterator

INF = 1 << 30  # 层号哨兵：比任何合法层号都大，表示"这一轮从这个点出发没有增广路"


def bfs_layers(lefts: list[int], adj: list[tuple[int, ...]], match_l: list[int],
               match_r: list[int], dist: list[int]) -> int:
    """给左部点分层，返回最短增广路的边数；一条增广路都没有时返回 INF。

    从每个未匹配左部点出发，沿"未匹配边 → 匹配边"交替走：走到右部点 y 后，
    下一步只能走 y 的匹配边到 match_r[y]，所以层号只需记在左部点上。
    第一次碰到未匹配右部点时得到的层号就是最短增广路长度，BFS 保证它最小。
    """
    queue = deque()
    for u in lefts:
        free = match_l[u] < 0          # 未匹配的左部点才是增广路起点
        dist[u] = 0 if free else INF
        if free:
            queue.append(u)
    shortest = INF
    while queue:
        x = queue.popleft()
        if dist[x] >= shortest:        # 同层及更深的点只会给出不更短的路，剪掉
            continue
        for y in adj[x]:
            z = match_r[y]
            if z < 0:                  # 右部点空闲：找到一条增广路
                shortest = dist[x] + 1
            elif dist[z] == INF:       # 已匹配右部点：顺着它的匹配边走到左部点 z
                dist[z] = dist[x] + 1
                queue.append(z)
    return shortest


def augment_all(lefts: list[int], adj: list[tuple[int, ...]], match_l: list[int],
                match_r: list[int], dist: list[int], shortest: int) -> int:
    """沿长度恰为 shortest 的增广路逐条增广，返回本轮增广条数。

    每个点在一轮里只允许被成功增广一次：匹配边一翻转，另一端就不再是自由点，
    搜索自然失败，因此一轮里这些增广路点不相交。失败时把该左部点层号置 INF，
    同一轮里不再重复搜索这棵失败的子树。
    """
    found = 0
    for root in lefts:
        if match_l[root] >= 0 or dist[root] >= shortest:
            continue                          # 已匹配或起点太深，做不了最短增广路
        stack = [(root, 0)]                   # (当前左部点, 下一个待试邻居的下标)
        path: list[tuple[int, int]] = []      # 交替路：(来的左部点, 指向它的右部点)
        while stack:
            x, i = stack[-1]
            neighbours = adj[x]
            descended = False
            while i < len(neighbours):
                y = neighbours[i]
                i += 1
                z = match_r[y]
                if z < 0:
                    if dist[x] + 1 != shortest:
                        continue              # 只有最短的增广路才在本轮使用
                    match_r[y] = x
                    match_l[x] = y
                    for px, py in path:       # 交替路整体翻转
                        match_r[py] = px
                        match_l[px] = py
                    found += 1
                    stack = []                # 这条路已经用掉，换下一个起点
                    descended = True
                    break
                if dist[z] == dist[x] + 1:    # 只能沿分层方向往下走
                    stack[-1] = (x, i)
                    path.append((x, y))
                    stack.append((z, 0))
                    descended = True
                    break
            if not stack:
                break
            if descended:
                continue
            dist[x] = INF                     # 这个点往下走不到自由点，本轮放弃
            stack.pop()
            if path:
                path.pop()
    return found


def max_matching(size: int, lefts: list[int], adj: list[tuple[int, ...]]) -> int:
    """Hopcroft–Karp：反复"分层 + 沿最短增广路批量增广"，直到不存在增广路。

    每轮把这一层能用的增广路一次用完，所以最多 O(√V) 轮。
    """
    match_l = [-1] * size   # 左部点的匹配对象，-1 表示未匹配
    match_r = [-1] * size   # 右部点的匹配对象，-1 表示未匹配
    dist = [INF] * size
    total = 0
    while True:
        shortest = bfs_layers(lefts, adj, match_l, match_r, dist)
        if shortest == INF:      # 由增广路定理，不存在增广路即已是最大匹配
            return total
        total += augment_all(lefts, adj, match_l, match_r, dist, shortest)


def read_board(n: int, t: int, data: Iterator[int]) -> tuple[int, bytearray]:
    """返回 (棋盘边长, 禁止格标记)；外圈也标记成禁止格，上下左右的越界判断直接省掉。"""
    width = n + 2
    banned = bytearray(width * width)
    for i in range(width):            # 四条边界
        banned[i] = banned[i * width] = banned[i * width + width - 1] = 1
        banned[width * (width - 1) + i] = 1
    for _ in range(t):
        x, y = next(data), next(data)
        banned[x * width + y] = 1     # 重复出现的禁止格由幂等赋值自然吸收
    return width, banned


def build_graph(n: int, banned: bytearray) -> tuple[list[tuple[int, ...]], list[int]]:
    """黑白染色建二分图，返回 (左部点邻接表, 左部点列表)。

    骨牌必然压住一黑一白：把 (行号 + 列号) 为偶数的可放格当左部点，
    每个左部点向上下左右四个非禁止格连边，最大匹配数就是最多骨牌数。
    """
    width = n + 2
    adj: list[tuple[int, ...]] = [()] * (width * width)
    lefts: list[int] = []
    for r in range(1, n + 1):
        base = r * width
        for c in range(1, n + 1):
            v = base + c
            if banned[v] or (r + c) & 1:
                continue
            lefts.append(v)
            adj[v] = tuple(w for w in (v - width, v + width, v - 1, v + 1) if not banned[w])
    return adj, lefts


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    t = next(data)
    width, banned = read_board(n, t, data)
    adj, lefts = build_graph(n, banned)
    print(max_matching(width * width, lefts, adj))


if __name__ == "__main__":
    solve()
