#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:34
# update_at: 2026-10-02 10:34

import sys
from bisect import bisect_left
from collections import deque

DIST: list[int] = []      # 每个点到根的总时长
UP: list[list[int]] = []  # UP[j][v]：v 的 2^j 级祖先，0 表示不存在
CH: list[list[int]] = []  # 以 1 为根的孩子表
ORDER: list[int] = []     # BFS 层序（不含根），倒序即自底向上
TOP: list[int] = []       # 每个点正上方的根之子，军队"原驻地"看它
WTOP: list[int] = []      # 根之子到根的边权（仅深度 1 有点义）
RC: list[int] = []        # 根的孩子，按边权升序
ARMY: list[int] = []      # 军队所在点，按到根时长降序
NEG_D: list[int] = []     # 对应的 -DIST，升序，供 bisect 判断能否走到首都
LOG = 0
M = 0


def lift(v: int, x: int) -> int:
    """倍增上跳：返回 x 小时内能到达的最高祖先（到不了首都）。"""
    threshold = DIST[v] - x  # 目标 dist 至少要这么大；为正数 ⇒ 不会跳到首都
    u = v
    for j in range(LOG - 1, -1, -1):
        a = UP[j][u]
        if a and DIST[a] >= threshold:
            u = a
    return u


def subtree_covered(vis: bytearray) -> bytearray:
    """自底向上标记：每个点的子树是否已被驻扎军队完整覆盖。"""
    cov = bytearray(len(DIST))
    for u in reversed(ORDER):
        if vis[u]:
            cov[u] = 1
            continue
        children = CH[u]
        if children:  # 叶子没有孩子：没军队驻扎就是没覆盖
            covered = 1
            for c in children:
                if not cov[c]:
                    covered = 0
                    break
            cov[u] = covered
    return cov


def feasible(x: int) -> bool:
    """判断 x 小时内能否控制疫情：上跳分流 → 覆盖统计 → 贪心匹配。"""
    vis = bytearray(len(DIST))
    split = bisect_left(NEG_D, -x)  # 前缀到不了首都，后缀可以
    for i in range(split):
        vis[lift(ARMY[i], x)] = 1
    cov = subtree_covered(vis)

    # 能走到首都的军队按剩余时间升序（到根时长降序），剩余时间不够回到原孩子的
    # 先留在原地把原孩子盖掉，剩下的进匹配池——这一步是"决策包容性"的特判
    pool: list[int] = []
    for i in range(split, M):
        v = ARMY[i]
        rest = x - DIST[v]
        son = TOP[v]
        if not cov[son] and rest < WTOP[son]:
            cov[son] = 1  # 原孩子还没盖住，且回不去：直接留在原地
        else:
            pool.append(rest)

    # 未覆盖的根之子按边权升序，剩余时间取"刚刚够用"的军队（双指针）
    j = 0
    pool_len = len(pool)
    for c in RC:
        if cov[c]:
            continue
        w = WTOP[c]
        while j < pool_len and pool[j] < w:
            j += 1
        if j == pool_len:
            return False
        j += 1
    return True


def solve() -> None:
    global LOG, M, RC, ARMY, NEG_D
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]
    total = 0  # 全部边权之和，充当二分上界
    for _ in range(n - 1):
        u, v, w = next(data), next(data), next(data)
        adj[u].append((v, w))
        adj[v].append((u, w))
        total += w

    # 从首都 BFS 定根：父亲、层序、到根时长、根之子
    DIST.extend([0] * (n + 1))
    CH.extend([] for _ in range(n + 1))
    TOP.extend([0] * (n + 1))
    WTOP.extend([0] * (n + 1))
    fa = [0] * (n + 1)
    seen = bytearray(n + 1)
    seen[1] = 1
    queue = deque([1])
    while queue:
        u = queue.popleft()
        for v, w in adj[u]:
            if seen[v]:
                continue
            seen[v] = 1
            DIST[v] = DIST[u] + w
            CH[u].append(v)
            fa[v] = u
            TOP[v] = v if u == 1 else TOP[u]
            if u == 1:
                WTOP[v] = w
            ORDER.append(v)
            queue.append(v)
    del adj, seen

    LOG = (n).bit_length()
    UP.extend([[0] * (n + 1) for _ in range(LOG)])
    for v in ORDER:
        UP[0][v] = fa[v]
    for j in range(1, LOG):
        row, prev = UP[j], UP[j - 1]
        for v in ORDER:
            row[v] = prev[prev[v]]

    M = next(data)
    ARMY = sorted((next(data) for _ in range(M)), key=lambda v: DIST[v], reverse=True)
    NEG_D = [-DIST[v] for v in ARMY]
    RC = sorted(CH[1], key=lambda c: WTOP[c])

    if M < len(CH[1]):  # 军队数少于根之子数，一个子树都分不到
        print(-1)
        return

    lo, hi = 0, total  # 边权全取，所有军队都能走到首都，必可行
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid):
            hi = mid
        else:
            lo = mid + 1
    print(lo)


if __name__ == "__main__":
    solve()
