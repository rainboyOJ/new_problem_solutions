#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 18:03
# update_at: 2026-10-01 18:03

import sys


def advance(dp: list[list[float]], p: float, gain: int, span: int, top_j: int) -> list[list[float]]:
    """做一次挑战的单层概率转移：行 = 成功数（截到 L），列 = 净容量（截到 ±m）。

    gain = -1 表示成功得到地图残片（净容量 -1），否则是成功获得的包包容量；
    top_j 是这次转移后可能达到的最大成功数下标（不超过 L）。
    """
    fail = 1 - p
    last_j = len(dp) - 1
    old = [row[:] for row in dp[:top_j + 1]]
    fresh: list[list[float]] = []
    for j, row in enumerate(old):
        nxt = [x * fail for x in row]  # 失败分支：状态原地不动
        if j == last_j:  # 成功数已封顶：成功后仍留在本档
            src = row if j == 0 else [x + y for x, y in zip(row, old[j - 1])]
        elif j > 0:
            src = old[j - 1]
        else:
            src = None
        if src is not None:
            weighted = [v * p for v in src]  # 成功分支：概率加权后的来源行
            if gain < 0:  # 残片：净容量整体左移 1 格（最低格概率恒为 0，可安全舍去）
                nxt[:] = [x + y for x, y in zip(nxt, weighted[1:])] + [nxt[-1]]
            elif gain >= span - 1:  # 增量越过上限，全部截到顶格
                nxt[-1] += sum(weighted)
            else:  # 未越界的左段平移，越界的右段截到顶格
                nxt[-1] += sum(weighted[span - gain:])
                nxt[gain:] = [x + y for x, y in zip(nxt[gain:], weighted)]
        fresh.append(nxt)
    return fresh + dp[len(fresh):]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, need, capacity = int(next(data)), int(next(data)), int(next(data))  # 挑战数 / 最低成功数 / 初始包容量
    # 成功概率：题面给的是百分数
    probs = [float(next(data)) / 100 for _ in range(n)]
    gains = [int(next(data)) for _ in range(n)]

    # 净容量 = 初始容量 + 获得的包容量 - 地图残片数；只需保留 [-m, m]，m 为残片总数
    frag_total = gains.count(-1)
    span = frag_total * 2 + 1
    dp = [[0.0] * span for _ in range(need + 1)]
    dp[0][min(capacity, frag_total) + frag_total] = 1.0

    for i, (p, a) in enumerate(zip(probs, gains), 1):
        dp = advance(dp, p, a, span, min(need, i))

    # 成功数 ≥ L 的概率全在第 L 行（封顶档），净容量 ≥ 0 即残片装得下
    print(f"{sum(dp[need][frag_total:]):.6f}")


if __name__ == "__main__":
    solve()
