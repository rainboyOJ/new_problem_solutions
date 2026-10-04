#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 16:38
# update_at: 2026-10-04 11:36

# 记 f[u] = 从 u 出发走到 N 的期望路径长度。青蛙在 u 时先均匀随机挑一条出边：
# f[u] = Σ_{u->v 长度 c} (c + f[v]) / out[u] = (Σc + Σf[v]) / out[u]。
# 右边只用到后继，所以在 DAG 上按拓扑序倒着推一遍即可，终点 f[N] = 0。

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))  # 读入游标：next() 顺序消费
    n, m = next(data), next(data)

    out_edges: list[list[int]] = [[] for _ in range(n + 1)]  # out_edges[u] = u 的出边编号
    edge_len_sum = [0] * (n + 1)  # Σ 出边长度
    end = [0] * m  # 第 i 条边的终点
    indeg = [0] * (n + 1)
    for i in range(m):
        a, b, c = next(data), next(data), next(data)  # 每条边固定 u v c 三个 token
        out_edges[a].append(i)
        edge_len_sum[a] += c
        end[i] = b
        indeg[b] += 1

    # Kahn 拓扑排序：入度为 0 的点入队，出队时把后继入度减 1；入队顺序就是拓扑序。
    # 在同一个列表里边遍历边追加，就等价于一个先进先出的队列。
    order = [u for u in range(1, n + 1) if indeg[u] == 0]
    for u in order:
        for i in out_edges[u]:
            v = end[i]
            indeg[v] -= 1
            if indeg[v] == 0:
                order.append(v)  # 追加到正在遍历的列表尾部 = 入队

    dp = [0.0] * (n + 1)
    for u in reversed(order):  # 逆拓扑序：算 f[u] 时所有后继的 f 都已就绪
        k = len(out_edges[u])
        if k and u != n:  # 走到终点就停下，终点自身不再产生期望长度
            dp[u] = (edge_len_sum[u] + sum(dp[end[i]] for i in out_edges[u])) / k
    print(f"{dp[1]:.2f}")


if __name__ == "__main__":
    solve()
