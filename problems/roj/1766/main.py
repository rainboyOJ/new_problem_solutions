#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 00:39
# update_at: 2026-10-08 00:39

import sys
from bisect import bisect_left

INF = 10 ** 9  # 无穷大：合法答案 < 5e8，与合法值相加也不会被误判（Python 整数不溢出）


def min_cost(w: list[int], a: int, b: int) -> int:
    """区间 DP：返回把整叠成绩单按批次全部发完的最小代价。

    一批不要求是原序列上的连续区间：设 S 为区间 [l,r] 里最后被取走的那批，则
    [l,r] 中不属于 S 的元素被 S 切成互不相干的空隙，每个空隙是独立的子问题。
    状态：
      dp[l][r]        把 [l,r] 当成独立一叠全部发完的最小代价（空区间为 0）
      G[l][r][x*V+y]  消掉 [l,r] 中不属于最后一批的元素的最小代价，要求最后一批
                      含位置 l、其分数排名落在 [x,y] 内（不含最后一批自身的代价）
      hh[s][r]        [s,r] 中 s 作为最后一批最左元素时的最优总代价
    """
    n = len(w)
    vals = sorted(set(w))
    V = len(vals)
    rank = [bisect_left(vals, x) for x in w]  # 位置 -> 压缩排名；原分数只用于算极差

    # 位置 l 若属于最后一批，则该批的排名区间 [x,y] 必须夹住 rank[l]。
    # pairs[l] 列出这些区间，idx[l] 是它们在 V*V 扁平表里的下标 x*V+y。
    pairs = [[(x, y) for x in range(rk + 1) for y in range(rk, V)] for rk in rank]
    idx = [[x * V + y for x, y in ps] for ps in pairs]

    dp = [[0] * n for _ in range(n + 1)]
    hh = [[INF] * n for _ in range(n)]
    G: list[list[list[int]]] = [[[] for _ in range(n)] for _ in range(n)]

    for length in range(1, n + 1):
        for l in range(n - length + 1):
            r = l + length - 1
            ps, ids = pairs[l], idx[l]
            cur = [INF] * (V * V)  # 排名不夹住 rank[l] 的组合永远保持 INF

            if length == 1:
                for i in ids:
                    cur[i] = 0  # 只留下 l 自己，不必先消掉任何元素
            else:
                for t, (x, y) in enumerate(ps):
                    i = ids[t]
                    best = INF
                    for k in range(l, r):
                        left = G[l][k][i]
                        if left >= INF:
                            continue
                        rk1 = rank[k + 1]
                        right = dp[k + 1][r]  # 右半 [k+1,r] 整段先取空
                        if x <= rk1 <= y:  # 右半也留下含 k+1 的一批，并入同一个最后一批
                            gv = G[k + 1][r][i]
                            if gv < right:
                                right = gv
                        cand = left + right
                        if cand < best:
                            best = cand
                    cur[i] = best
            G[l][r] = cur

            # 结算最后一批：极差用原分数算，取所有可行区间里最小的一批代价
            hh[l][r] = min(cur[i] + a + b * (vals[y] - vals[x]) ** 2 for (x, y), i in zip(ps, ids))

            # 枚举最后一批的最左位置 s：[l,s-1] 是 s 左边的空隙，先独立取空
            dp[l][r] = min((0 if s == l else dp[l][s - 1]) + hh[s][r] for s in range(l, r + 1))

    return dp[0][n - 1]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a, b = next(data), next(data)
    w = [next(data) for _ in range(n)]
    print(min_cost(w, a, b))


if __name__ == "__main__":
    solve()
