#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 14:01
# update_at: 2026-10-01 14:01

import sys
from collections import defaultdict, deque


def least_cost(n: int, adj: list[list[tuple[int, int]]], price: list[int],
               cap: int, start: int, target: int) -> int | None:
    """分层图最短路：问 (城市, 油量) 状态图上从 (start,0) 走到任意 target 状态的最少油钱。

    用 Dial 桶队列代替二叉堆：每步转移的花费增量 ≤ 最大油价 100，
    桶下标（已花油钱）单调递增，只有加油转移才产生新桶，空桶区间可用 last 剪枝。
    """
    buckets: defaultdict[int, deque[tuple[int, int]]] = defaultdict(deque)
    dist = [[1 << 30] * (cap + 1) for _ in range(n)]  # dist[u][f]：到达 u 且剩 f 升的最少油钱
    dist[start][0] = 0
    buckets[0].append((start, 0))
    pending = 1  # 桶里还没处理的状态总数
    last = 0     # 最远的非空桶下标，越过它还没事可做就说明 target 不可达

    idx = 0
    while pending:
        if idx > last:
            return None  # 没有任何更贵的加油转移在等待，target 到不了
        bucket = buckets.get(idx)
        if not bucket:
            idx += 1
            continue
        while bucket:  # 同层内油钱相同；开车不花钱，在本层内继续扩展
            u, f = bucket.popleft()
            pending -= 1
            if dist[u][f] != idx:  # 入桶后又出现过更便宜的记录，此条已过期
                continue
            if u == target:
                return idx  # 油钱单调不降，首次取出 target 即最优
            p = price[u]
            if f < cap and idx + p < dist[u][f + 1]:  # 在 u 加 1 升油，钱变多、进新桶
                dist[u][f + 1] = idx + p
                buckets[idx + p].append((u, f + 1))
                pending += 1
                if idx + p > last:
                    last = idx + p
            for v, d in adj[u]:  # 油够就开车去 v，油量减少、花费不变、留在本层
                nf = f - d
                if nf >= 0 and idx < dist[v][nf]:
                    dist[v][nf] = idx
                    bucket.append((v, nf))
                    pending += 1
        idx += 1
    return None


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    price = [next(data) for _ in range(n)]
    adj: list[list[tuple[int, int]]] = [[] for _ in range(n)]
    for _ in range(m):
        u, v, d = next(data), next(data), next(data)
        adj[u].append((v, d))
        adj[v].append((u, d))  # 无向图，两条反向边

    q = next(data)
    out = []
    for _ in range(q):
        cap, start, target = next(data), next(data), next(data)
        ans = least_cost(n, adj, price, cap, start, target)
        out.append('impossible' if ans is None else str(ans))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
