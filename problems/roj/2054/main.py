#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 05:39
# update_at: 2026-10-01 05:39

import sys
from collections import deque

# 骑士的 8 种走法：(列偏移, 行偏移)，即"日"字形的八个方向
KNIGHT_STEPS = ((1, 2), (2, 1), (2, -1), (1, -2), (-1, -2), (-2, -1), (-2, 1), (-1, 2))
INF = 10**9  # 不可达哨兵：只参与取最小值，不会与真实步数混淆


def knight_dist(src: int, moves: tuple[tuple[int, ...], ...]) -> list[int]:
    """骑士从 src 出发到每个格子的最少步数，到不了记 -1。"""
    dist = [-1] * len(moves)
    dist[src] = 0
    queue = deque([src])
    while queue:
        u = queue.popleft()
        step = dist[u] + 1
        for v in moves[u]:
            if dist[v] < 0:  # 边长全为 1，第一次到达就是最短路
                dist[v] = step
                queue.append(v)
    return dist


def carry_min(dist: list[int], walk: list[int], moves: tuple[tuple[int, ...], ...]) -> list[int]:
    """E[t] = min_u (D_k(u) + walk(u) + D(u,t))：这名骑士绕到 u 接国王、再赶到 t 的代价。

    国王自己走到 u 要 walk(u) 步，所以种子取 E[u] = D_k(u) + walk(u)；
    再沿骑士图做一次多源 BFS。种子最大值就是值域上界，用桶（Dial 队列）代替堆。
    """
    limit = max(d + w for d, w in zip(dist, walk) if d >= 0)
    best = [INF] * len(moves)
    buckets = [[] for _ in range(limit + 1)]
    for u, (d, w) in enumerate(zip(dist, walk)):
        if d >= 0 and d + w < best[u]:
            best[u] = d + w
            buckets[d + w].append(u)
    for d in range(limit + 1):
        for u in buckets[d]:
            if best[u] < d:  # 这个格子已被更小的种子值刷新，桶里的副本作废
                continue
            for v in moves[u]:
                if d + 1 < best[v]:
                    best[v] = d + 1
                    buckets[d + 1].append(v)
    return best


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    rows, cols = int(next(data)), int(next(data))
    king_col, king_row = next(data)[0] - 65, int(next(data)) - 1
    # 之后每两个 token 是一个骑士：列字母 + 行号
    knight_ids = [(int(r) - 1) * cols + (c[0] - 65) for c, r in zip(data, data)]

    n = rows * cols
    moves = tuple(  # 先把棋盘外剔除，BFS 时不用再判边界
        tuple((r + dr) * cols + (c + dc) for dc, dr in KNIGHT_STEPS
              if 0 <= c + dc < cols and 0 <= r + dr < rows)
        for r in range(rows) for c in range(cols)
    )
    # 国王单独走到某格所需步数（切比雪夫距离），只需要算一次
    walk = [max(abs(c - king_col), abs(r - king_row)) for r in range(rows) for c in range(cols)]

    base = [0] * n      # base[t]：所有骑士各自直奔 t 的步数和
    gain = [INF] * n    # gain[t]：min over k of (E_k[t] - D_k(t))，携带国王带来的增量
    reach = [0] * n     # reach[t]：能走到 t 的骑士数，等于骑士总数才能当集合点
    for k in knight_ids:
        dist = knight_dist(k, moves)
        carry = carry_min(dist, walk, moves)
        for t, d in enumerate(dist):
            if d < 0:
                continue
            base[t] += d
            reach[t] += 1
            delta = carry[t] - d
            if delta < gain[t]:
                gain[t] = delta

    # 集合点 t 的代价：国王自己走过去 walk[t]，或由某名骑士接送（gain[t]），取较小者
    print(min(
        base[t] + min(walk[t], gain[t])
        for t in range(n)
        if reach[t] == len(knight_ids)
    ))


if __name__ == "__main__":
    solve()
