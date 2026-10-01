#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:44
# update_at: 2026-10-01 23:44

import sys
from collections import deque
from operator import gt, lt

INF = 1 << 60


def build_csr(n: int, edges: list[tuple[int, int, int]]) -> tuple[list[int], list[int], list[int]]:
    """把边表建成链式前向星；z=2 的双向边在两个方向各挂一条。返回 (head, nxt, to)。"""
    head = [0] * (n + 1)
    nxt = [0] * (2 * len(edges) + 1)
    to = [0] * (2 * len(edges) + 1)
    cnt = 1  # 边从 1 号开始编号，head 为 0 表示没有出边
    for x, y, z in edges:
        pairs = [(x, y), (y, x)] if z == 2 else [(x, y)]  # 双向边存两条
        for u, v in pairs:
            to[cnt] = v
            nxt[cnt] = head[u]
            head[u] = cnt
            cnt += 1
    return head, nxt, to


def spfa(n: int, head: list[int], nxt: list[int], to: list[int], price: list[int],
         start: int, init: int, combine, is_better) -> list[int]:
    """从 start 出发，沿边传播“路径上价格的极值”：combine=min 得最小买价，=max 得最大卖价。

    best[v] = 起点到 v 的所有路径上，combine(路径上各点价格) 的最优值；
    每次松弛取 combine(best[u], price[v])，队列 + inq 就是标准 SPFA。
    不可达点保持初值 init：min 版为 INF，max 版为 -INF。
    """
    best = [init] * (n + 1)
    best[start] = price[start]
    inq = bytearray(n + 1)
    inq[start] = 1
    dq = deque([start])
    while dq:
        u = dq.popleft()
        inq[u] = 0
        e = head[u]
        while e:
            v = to[e]
            nd = combine(best[u], price[v])
            if is_better(nd, best[v]):
                best[v] = nd
                if not inq[v]:
                    inq[v] = 1
                    dq.append(v)
            e = nxt[e]
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    price = [0] + [next(data) for _ in range(n)]

    edges = [(next(data), next(data), next(data)) for _ in range(m)]

    # 正图上从 1 做 min：mn[v] = 从 1 走到 v 的路上能买到的最低价
    head, nxt, to = build_csr(n, edges)
    mn = spfa(n, head, nxt, to, price, 1, INF, min, lt)

    # 反图上从 n 做 max：mx[v] = 从 v 走到 n 的路上能卖出的最高价
    rhead, rnxt, rto = build_csr(n, [(y, x, z) for x, y, z in edges])
    mx = spfa(n, rhead, rnxt, rto, price, n, -INF, max, gt)

    # 买卖都发生在 v：两头都可达才有定义，等初值说明该端不可达
    print(max((s - b for b, s in zip(mn, mx)
               if b != INF and s != -INF), default=0))


if __name__ == "__main__":
    solve()
