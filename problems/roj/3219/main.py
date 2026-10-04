#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 02:35
# update_at: 2026-10-02 02:42

import sys
from collections import deque

WALL = ord('#')    # 只有墙壁挡光；草地 '*' 透光，所以「极大段」只被墙壁切断
EMPTY = ord('o')   # 只有空地能放机器人与被激光打到，也只有空地格产生一条边
INF = 1 << 30      # 层号哨兵：比任何合法层号都大，表示该横向段在本轮分层里到不了


def row_segments(grid: list[bytes], rows: int, cols: int) -> tuple[list[list[int]], int]:
    """每格所属的横向极大非墙壁段编号（墙壁记 -1），返回编号表与横向段总数。

    段内任意两格之间没有墙壁，机器人沿行方向必能互相打到；
    草地不重置段号，否则 `o*o` 这种「隔着草地互射」的冲突会被漏掉。
    """
    table: list[list[int]] = []
    total = 0
    for r in range(rows):
        row = grid[r]
        ids: list[int] = []
        seg = -1                      # 上一个格子是墙壁（或行首）时置 -1，表示还没进段
        for c in range(cols):
            if row[c] == WALL:
                seg = -1
            elif seg < 0:
                seg = total           # 一段新的横向极大段从这里开始
                total += 1
            ids.append(seg)
        table.append(ids)
    return table, total


def build_adjacency(
    grid: list[bytes], table: list[list[int]], lefts: int, rows: int, cols: int
) -> tuple[list[list[int]], int]:
    """建二分图：左部是横向段、右部是纵向段，每个空地格连一条边。

    返回 (左部点的邻接表, 右部点个数)。纵向段沿列扫描得到，
    段内每个空地格所在的横向段编号就是它的一个邻居。
    """
    adj: list[list[int]] = [[] for _ in range(lefts)]
    vertical_cnt = 0
    for c in range(cols):
        r = 0
        while r < rows:
            if grid[r][c] == WALL:
                r += 1
                continue
            start = r
            while r < rows and grid[r][c] != WALL:
                r += 1
            # 这一段上下两端顶住墙壁或边界，段内每个空地格都向它连一条边
            for i in range(start, r):
                if grid[i][c] == EMPTY:
                    adj[table[i][c]].append(vertical_cnt)
            vertical_cnt += 1
    return adj, vertical_cnt


def bfs_layers(
    adj: list[list[int]], lefts: int, match_l: list[int], match_r: list[int], dist: list[int]
) -> int:
    """给左部点分层，返回最短增广路的边数；一条增广路都没有时返回 INF。

    从每个未匹配横向段出发，沿「未匹配边 → 匹配边」交替走：走到纵向段 v 后，
    下一步只能走 v 的匹配边到 match_r[v]，没有分支，所以层号只需记在左部点上。
    第一次碰到空闲纵向段时的层号就是最短增广路长度，BFS 保证它最小。
    """
    queue: deque[int] = deque()
    for u in range(lefts):
        free = match_l[u] < 0          # 未匹配的左部点才是增广路起点
        dist[u] = 0 if free else INF
        if free:
            queue.append(u)
    shortest = INF
    while queue:
        u = queue.popleft()
        if dist[u] >= shortest:        # 同层及更深的点只会给出不更短的路，剪掉
            continue
        for v in adj[u]:
            w = match_r[v]
            if w < 0:                  # 纵向段空闲：找到一条增广路
                shortest = dist[u] + 1
            elif dist[w] == INF:       # 已匹配的纵向段：顺着匹配边走到左部点 w
                dist[w] = dist[u] + 1
                queue.append(w)
    return shortest


def augment(
    root: int, adj: list[list[int]], match_l: list[int], match_r: list[int],
    dist: list[int], shortest: int
) -> bool:
    """只沿分层方向找一条长度恰为 shortest 的增广路并翻转，返回是否成功。

    显式栈代替递归：帧是 [当前横向段, 下一个待试邻居下标]，
    path 记录已走过的未匹配边，命中空闲纵向段时整条交替路一起翻转。
    """
    stack = [[root, 0]]
    path: list[tuple[int, int]] = []   # 交替路上的未匹配边 (横向段, 纵向段)
    while stack:
        frame = stack[-1]
        u = frame[0]
        if frame[1] == len(adj[u]):    # 这个横向段的所有出路都试过，回溯
            dist[u] = INF              # 本轮再也走不到空闲纵向段，剪掉
            stack.pop()
            if path:
                path.pop()
            continue
        v = adj[u][frame[1]]
        frame[1] += 1
        w = match_r[v]
        if w < 0:
            if dist[u] + 1 != shortest:
                continue               # 只有最短的增广路才在本轮使用
            match_l[u], match_r[v] = v, u
            for pu, pv in path:        # 交替路整体翻转，未匹配边全部变成匹配边
                match_l[pu], match_r[pv] = pv, pu
            return True
        if dist[w] == dist[u] + 1:     # 只能沿分层方向往下走
            path.append((u, v))
            stack.append([w, 0])
    return False


def hopcroft_karp(adj: list[list[int]], lefts: int, rights: int) -> int:
    """Hopcroft–Karp：反复「分层 + 沿最短增广路批量增广」，返回最大匹配数。

    每次成功的增广让匹配数 +1，所以最大匹配数 = 最多能同时放下的机器人个数；
    长度相同的增广路互不相交，一轮能一次增广多条，轮数不超过 O(sqrt(V))。
    """
    match_l = [-1] * lefts    # 横向段 -> 配到的纵向段，-1 表示还没配
    match_r = [-1] * rights   # 纵向段 -> 配到的横向段
    dist = [INF] * lefts
    matched = 0
    while True:
        shortest = bfs_layers(adj, lefts, match_l, match_r, dist)
        if shortest == INF:       # 由增广路定理，找不到增广路即已是最大匹配
            return matched
        for root in range(lefts):
            free = match_l[root] < 0        # 只有仍未匹配的横向段才能当增广路起点
            if free and augment(root, adj, match_l, match_r, dist, shortest):
                matched += 1


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    T = int(next(data))

    for case in range(1, T + 1):
        rows, cols = int(next(data)), int(next(data))
        grid = [next(data) for _ in range(rows)]

        table, lefts = row_segments(grid, rows, cols)           # 左部顶点：横向极大段
        adj, rights = build_adjacency(grid, table, lefts, rows, cols)  # 右部顶点：纵向极大段
        out += [f"Case :{case}", str(hopcroft_karp(adj, lefts, rights))]

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
