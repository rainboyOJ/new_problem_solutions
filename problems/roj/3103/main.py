#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:20
# update_at: 2026-10-01 17:37

import sys
from collections.abc import Iterable

INF = float("inf")  # 期望 DP 里"用这么多次申请走不到"的哨兵
BIG = 10**9         # 最短路里"没有路"的哨兵：远大于任意教室对的最远距离（< 300*100）


def all_pairs(dist: list[list[int]], v: int, edges: Iterable[tuple[int, int, int]]) -> None:
    """原地 Floyd–Warshall：跑完后 dist[i][j] 是教室 i 到 j 的最少体力。"""
    for i in range(v):
        dist[i][i] = 0                      # 教室自己到自己，同时也覆盖掉输入里的自环
    for a, b, w in edges:
        if w < dist[a][b]:                  # 重边只留最短的那条
            dist[a][b] = dist[b][a] = w
    for k in range(v):
        dk = dist[k]
        for di in dist:
            dik = di[k]
            if dik < BIG:                   # 经 k 不可达就整行跳过，省掉一次全行扫描
                for j in range(v):
                    alt = dik + dk[j]
                    if alt < di[j]:
                        di[j] = alt


def expected_cost(dist: list[list[int]], c: list[int], d: list[int],
                  k: list[float], m: int) -> float:
    """期望 DP：返回"移动体力总和"的期望最小值。

    只有第 t+1 门课的教室确定之后，第 t 段的移动距离才确定，所以"第 t 门是否申请"
    必须留在状态里。dp0[j] / dp1[j] 表示用了 j 次申请、且第 t 门不申请 / 申请时，
    前 t-1 段移动体力期望和的最小值；每轮把第 t 段的期望并进来。
    """
    dp0 = [0.0] + [INF] * m                  # 第 1 门不申请：用掉 0 次申请
    dp1 = [INF] * (m + 1)                    # 第 1 门申请：恰好用掉 1 次申请
    if m:
        dp1[1] = 0.0

    for t in range(len(c) - 1):
        cc = dist[c[t]][c[t + 1]]            # 上、下两门都不申请
        cd = dist[c[t]][d[t + 1]]            # 只有第 t+1 门申请且通过
        dc = dist[d[t]][c[t + 1]]            # 只有第 t 门申请且通过
        dd = dist[d[t]][d[t + 1]]            # 两门都申请且都通过
        win = k[t + 1]                       # 第 t+1 门申请通过的概率
        lose = 1 - k[t]                      # 第 t 门申请被拒的概率
        # 四种"上/下是否申请"的组合下，这一段的期望距离：
        cost01 = (1 - win) * cc + win * cd                     # 上不申请、下申请
        cost10 = lose * cc + (1 - lose) * dc                   # 上申请、下不申请
        cost11 = lose * cost01 + (1 - lose) * ((1 - win) * dc + win * dd)
        head0, head1 = dp0[:m], dp1[:m]      # 本轮申请数要 +1，旧数组只用到前 m 位
        dp0 = [min(a + cc, b + cost10) for a, b in zip(dp0, dp1)]
        dp1 = [INF] + [min(a + cost01, b + cost11) for a, b in zip(head0, head1)]

    return min(min(dp0), min(dp1))


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    n, m, v, e = map(int, tokens[:4])
    m = min(m, n)                                        # 申请超过 n 次也用不完
    c = [x - 1 for x in map(int, tokens[4:4 + n])]
    d = [x - 1 for x in map(int, tokens[4 + n:4 + 2 * n])]
    k = list(map(float, tokens[4 + 2 * n:4 + 3 * n]))
    edge_tokens = list(map(int, tokens[4 + 3 * n:]))     # 边按 a, b, w 依次平铺
    edges = [(edge_tokens[i] - 1, edge_tokens[i + 1] - 1, edge_tokens[i + 2])
             for i in range(0, 3 * e, 3)]

    dist = [[BIG] * v for _ in range(v)]
    all_pairs(dist, v, edges)

    # 精确到分。直接写 f"{ans:.2f}" 会踩两个坑：Python 默认银行家舍入（.005 向偶数靠），
    # 以及 1.005*100 = 100.49999999999999 这类表示误差；先转整数分四舍五入，+1e-9 兜住后者。
    cents = int(expected_cost(dist, c, d, k, m) * 100 + 0.5 + 1e-9)
    print(f"{cents / 100:.2f}")


if __name__ == "__main__":
    solve()
