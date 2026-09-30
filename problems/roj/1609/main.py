#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:45
# update_at: 2026-09-30 21:45

import sys
from collections import deque
from itertools import accumulate

INF = 10**30  # 不可达 DP 值的哨兵，远大于任何合法答案


def dp_layer(prev: list[int], limit: list[int], pre: list[int]) -> list[int]:
    """多用一只饲养员推进一层 DP：f[r] = min_k prev[k] + (r-k)*a_r - (pre[r]-pre[k])。

    猫按 a 升序排好后，每只饲养员接走的必是一段连续的猫，段 (k, r] 的最优出发时刻
    就是段尾 a_r；把转移整理成 f[r] = r*a_r - pre[r] + min_k {(prev[k]+pre[k]) - k*a_r}，
    每个 k 就是一条斜率 -k、截距 prev[k]+pre[k] 的直线。加入序斜率递减、查询点
    a_r 递增（非降），用单调队列维护下凸壳，摊还每步 O(1)。
    """
    dq: deque[tuple[int, int]] = deque()  # (斜率, 截距)，斜率自队头向队尾递减
    n = len(limit)
    f = [INF] * (n + 1)
    for r in range(n + 1):
        if prev[r] < INF:  # 不可达的切点 k 不入壳
            m, b = -r, prev[r] + pre[r]
            # 队尾直线的生效区间被新交点截空（x12 <= x23）→ 它永远取不到最小值
            while len(dq) >= 2 and (b - dq[-1][1]) * (dq[-2][0] - dq[-1][0]) <= (dq[-1][1] - dq[-2][1]) * (dq[-1][0] - m):
                dq.pop()
            dq.append((m, b))
        if r == 0:
            f[0] = 0  # 0 只猫的费用恒为 0，它也是下一层 k=0 的直线来源
            continue
        x = limit[r - 1]  # a_r：段尾猫要求饲养员不早于它出发
        # 查询点递增，队头若已不如第二条就出队
        while len(dq) >= 2 and dq[0][0] * x + dq[0][1] >= dq[1][0] * x + dq[1][1]:
            dq.popleft()
        f[r] = r * x - pre[r] + dq[0][0] * x + dq[0][1]
    return f


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    N, M, P = next(data), next(data), next(data)

    # 前缀距离：reach[h] = 1 号山走到 h 号山需要的时间
    reach = [0] * (N + 1)
    for h in range(2, N + 1):
        reach[h] = reach[h - 1] + next(data)

    # 每只猫只依赖 a = T - s[H]：饲养员出发不早于 a 才接得到，等待 = 出发时刻 - a
    cats = [(next(data), next(data)) for _ in range(M)]  # (H, T)，题面顺序
    limit = sorted(t - reach[h] for h, t in cats)  # a_1..a_M 升序
    pre = list(accumulate(limit, initial=0))  # a 的前缀和，pre[r] = sum_{i<=r} a_i

    prev = [INF] * (M + 1)
    prev[0] = 0  # 0 只饲养员一只猫也接不到
    for _ in range(P):
        cur = dp_layer(prev, limit, pre)
        if cur == prev:  # 已到不动点：再加饲养员结果也不会变
            break
        prev = cur
    print(prev[M])


if __name__ == "__main__":
    solve()
