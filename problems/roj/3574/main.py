#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:28
# update_at: 2026-10-02 08:28

import sys

INF = 10**9  # 没有任何买点能到达时的哨兵（价格上界只有 100）


def walk(start: int, adj: list[list[int]]) -> list[bool]:
    """沿邻接表标出从 start 出发能到达的全部城市（迭代遍历，避免深递归）。"""
    seen = [False] * len(adj)
    seen[start] = True
    stack = [start]
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if not seen[v]:
                seen[v] = True
                stack.append(v)
    return seen


def buy_floor(price: list[int], out: list[list[int]], from1: list[bool]) -> list[int]:
    """buy_floor[u] = 能到达 u 的可买入城市中的最低价；无买点到达则保持 INF。

    按价格 1→100 逐层做多源传播：本层中"属于 A（from1）且尚未被更低价覆盖"
    的城市成为买点，沿出边把 floor 填成本层价格。低层先跑，所以高层只填 INF，
    每个城市至多入栈一次、每条出边至多扫描一次。
    """
    by_price: list[list[int]] = [[] for _ in range(101)]  # 价格 1~100，按价分桶
    for u in range(1, len(price)):
        by_price[price[u]].append(u)

    floor = [INF] * len(price)
    for cost in range(1, 101):
        for src in by_price[cost]:
            if not from1[src] or floor[src] <= cost:  # 买不到的城市 / 已被更便宜买点覆盖
                continue
            floor[src] = cost
            stack = [src]
            while stack:
                u = stack.pop()
                for v in out[u]:
                    if floor[v] > cost:  # 还没有任何买点到达
                        floor[v] = cost
                        stack.append(v)
    return floor


def solve() -> None:
    readline = sys.stdin.buffer.readline  # 逐行读入，不一次性 split 全文（省一份 token 列表的内存）
    n, m = map(int, readline().split())
    price = [0] + list(map(int, readline().split()))

    out: list[list[int]] = [[] for _ in range(n + 1)]  # 正向出边
    rev: list[list[int]] = [[] for _ in range(n + 1)]  # 反向出边（原道路的入边）
    for _ in range(m):
        x, y, z = map(int, readline().split())
        out[x].append(y)
        rev[y].append(x)
        if z == 2:  # 双向道路拆成两条单向边
            out[y].append(x)
            rev[x].append(y)

    from1 = walk(1, out)  # 买入城市必须能从 1 出发到达
    to_n = walk(n, rev)   # 卖出城市必须还能走到 n
    floor = buy_floor(price, out, from1)

    # 卖点 s 合法 ⇔ s 能走到 n 且有买点能到达 s；此时 floor[s] <= price[s]，答案天然非负
    ans = max(price[s] - floor[s] for s in range(1, n + 1) if to_n[s] and floor[s] < INF)
    print(ans)


if __name__ == "__main__":
    solve()
