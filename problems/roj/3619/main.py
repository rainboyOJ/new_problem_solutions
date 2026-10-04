#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:06
# update_at: 2026-10-02 11:07

import sys

MOD = 10007  # 联合权值之和的输出模数


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    adj: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = next(data), next(data)
        adj[u].append(v)
        adj[v].append(u)
    w = [0] + [next(data) for _ in range(n)]

    total = 0  # 有序点对联合权值之和（先保留精确值，最后再取模）
    best = 0   # 联合权值最大值

    # 距离为 2 的点对 (x, z) 必有唯一中转点 y：x、z 都是 y 的邻居。
    # 枚举每个中转点 y，把它的邻居权值列表 ws 一次性统计完。
    for u in range(1, n + 1):
        ws = [w[v] for v in adj[u]]  # 经过 u 中转的有序对，权值都来自这里
        s = sum(ws)

        # 有序对之和 = Σ_{i≠j} wi·wj = (Σw)² − Σw²，与无序对的 (Σw)²−Σw² 除以 2 相区分
        total += s * s - sum(x * x for x in ws)

        # 经过 u 的最大联合权值 = 邻居权值中最大与次大的乘积；度 < 2 时 m2 保持 0
        m1 = m2 = 0
        for x in ws:
            if x > m1:
                m1, m2 = x, m1
            elif x > m2:
                m2 = x
        best = max(best, m1 * m2)

    print(best, total % MOD)


if __name__ == "__main__":
    solve()
