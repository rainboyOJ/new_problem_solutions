#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 15:31
# update_at: 2026-09-30 15:31

import sys
from collections import deque

HOURS = 24   # 一天 24 个整点区间
SHIFT = 8    # 每人连续工作恰好 8 小时


def feasible(adj: list[list[tuple[int, int]]], target: int) -> bool:
    """跑最长路判断约束是否相容，并检查 S(24) 恰好等于 target。

    差分约束中 S(24) >= target 与 S(24) <= target 两条边已把 S(24) 钉死；
    若约束互相矛盾就会出现正环，此时某点会被反复松弛，超过 HOURS 轮即可判定。
    """
    dist = [0] * (HOURS + 1)
    in_queue = [True] * (HOURS + 1)
    queue = deque(range(HOURS + 1))  # 超级源点：所有点一起入队，等价于各连一条 0 权边
    rounds = [0] * (HOURS + 1)       # 每个点被成功松弛的次数，超过 HOURS 次说明有正环
    while queue:
        u = queue.popleft()
        in_queue[u] = False
        du = dist[u]  # 弹出时才读，保证用的是 u 的最新距离
        for v, w in adj[u]:
            if du + w > dist[v]:
                dist[v] = du + w
                rounds[v] += 1
                if rounds[v] > HOURS:
                    return False  # 正环：约束互相矛盾
                if not in_queue[v]:
                    in_queue[v] = True
                    queue.append(v)
    return dist[HOURS] >= target


def build(need: list[int], supply: list[int], total: int) -> list[list[tuple[int, int]]]:
    """按前缀和 S(i) = x(0)+...+x(i-1) 建图，边 (v, w) 表示 S(v) >= S(u) + w。

    need[i] 是第 i 个整点区间的需求 R(i)，supply[i] 是 t_i = i 的申请人数，
    total 是假定的总雇佣人数 M = S(24)。
    """
    adj: list[list[tuple[int, int]]] = [[] for _ in range(HOURS + 1)]
    for i in range(HOURS):
        adj[i].append((i + 1, 0))            # S(i+1) >= S(i)：前缀不减，即 x(i) >= 0
        adj[i + 1].append((i, -supply[i]))   # S(i) >= S(i+1) - c(i)：x(i) <= c(i)
    for i in range(HOURS):
        start = i - SHIFT + 1                                   # 覆盖第 i 小时的起点区间左端
        if start >= 0:
            adj[start].append((i + 1, need[i]))                 # 同一天：S(i+1) - S(start) >= R(i)
        else:
            # 跨午夜：S(i+1) + (M - S(i+17)) >= R(i)，即 S(i+1) >= S(i+17) + R(i) - M
            adj[start + HOURS].append((i + 1, need[i] - total))
    adj[0].append((HOURS, total))            # S(24) >= S(0) + M
    adj[HOURS].append((0, -total))           # S(0) >= S(24) - M，把 S(24) 锁成 M
    return adj


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        need = [next(data) for _ in range(HOURS)]
        n = next(data)
        supply = [0] * HOURS  # 每个起始时刻的申请者人数，即 x(i) 的上界
        for _ in range(n):
            supply[next(data)] += 1

        # 可行性对 M 单调：多雇一个已申请的人不会破坏任何时段，故二分最小 M。
        lo, hi = 0, n
        while lo < hi:
            mid = (lo + hi) // 2
            if feasible(build(need, supply, mid), mid):
                hi = mid
            else:
                lo = mid + 1

        out.append(str(lo) if feasible(build(need, supply, lo), lo) else "No Solution")

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
