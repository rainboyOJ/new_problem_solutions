#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:22
# update_at: 2026-09-30 21:22

import sys
from array import array
from collections import deque

NEG = -10**18  # 不可达哨兵：真实钱数下界约 -2000×2000×2000 = -8e9，远离此值


def transfer_buy(base: array, price: int, limit: int, max_p: int, dp: array) -> None:
    """买入转移：对每个 j，从窗口 j' ∈ [j-limit, j-1] 里取 base[j']-price*(j-j') 的最大值写进 dp。"""
    q: deque[int] = deque()  # 单调队列存下标，按 base[j']+price*j' 单调递减，队头即窗口最大
    for j in range(1, max_p + 1):
        nj = j - 1  # 窗口右端新进来的持股数
        v = base[nj] + price * nj
        while q and base[q[-1]] + price * q[-1] <= v:
            q.pop()
        q.append(nj)
        out = j - limit - 1  # 刚滑出窗口左端的持股数；它是队里最小下标，若在则必在队头
        if out >= 0 and q[0] == out:
            q.popleft()
        best = q[0]
        cand = base[best] + price * (best - j)  # = base[best] - price*(j-best)
        if cand > dp[j]:
            dp[j] = cand


def transfer_sell(base: array, price: int, limit: int, max_p: int, dp: array) -> None:
    """卖出转移：对每个 j，从窗口 j' ∈ [j+1, j+limit] 里取 base[j']+price*(j'-j) 的最大值写进 dp。"""
    q: deque[int] = deque()
    for j in range(max_p - 1, -1, -1):  # 窗口整体左移，从大到小枚举 j
        while q and q[-1] > j + limit:  # 右端（下标最大者）先滑出窗口
            q.pop()
        nj = j + 1  # 窗口左端新进来的持股数
        v = base[nj] + price * nj
        while q and base[q[0]] + price * q[0] <= v:  # 队头被更晚过期的更大值压制，弹出
            q.popleft()
        q.appendleft(nj)
        best = q[-1]  # 队里按值单调递增，队尾即窗口最大
        cand = base[best] + price * (best - j)  # = base[best] + price*(best-j)
        if cand > dp[j]:
            dp[j] = cand


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    days, max_p, W = next(data), next(data), next(data)
    AP = [0] * days  # 每天买入价
    BP = [0] * days  # 每天卖出价
    AS = [0] * days  # 每天一次买入的股数上限
    BS = [0] * days  # 每天一次卖出的股数上限
    for i in range(days):
        AP[i], BP[i], AS[i], BS[i] = next(data), next(data), next(data), next(data)

    # 环形历史快照：第 d 天结束时的持股状态；第 i 天交易只回看 d = i-W-1 的快照
    ring = W + 2
    day0 = array("q", [0] + [NEG] * max_p)  # 开盘前：0 股 0 钱，唯一可达状态
    hist: list[array | None] = [None] * ring
    hist[0] = day0
    dp = day0  # 截至昨天的状态；每天先原样继承（当天不交易）

    for day in range(1, days + 1):
        prev_day = day - W - 1  # 两次交易至少隔 W 天：上次交易最晚在 prev_day
        base = day0 if prev_day < 0 else hist[prev_day % ring]
        dp = array("q", dp)  # 继承「昨天也不交易」
        if AS[day - 1]:  # 买入：多持有 1..AS 股，每股花 AP
            transfer_buy(base, AP[day - 1], AS[day - 1], max_p, dp)
        if BS[day - 1]:  # 卖出：少持有 1..BS 股，每股收 BP
            transfer_sell(base, BP[day - 1], BS[day - 1], max_p, dp)
        hist[day % ring] = dp

    print(max(dp))  # 结束时持股任意（不交易就是 0 股），取钱数最大


if __name__ == "__main__":
    solve()
