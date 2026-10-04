#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:01
# update_at: 2026-10-02 13:01

import sys
from collections import deque

NEG = -10**18  # 不可达哨兵：合法分数和最小只到 -n·max|s_i| = -5×10^10，哨兵区不会被误判


def check(g: int, xs: list[int], ss: list[int], d: int, k: int) -> bool:
    """花 g 个金币改造后能否拿到至少 k 分：单调队列滑窗 DP，够分即提前返回。"""
    lo = max(1, d - g)  # 改进后最短弹跳距离（题面规定至少为 1）
    hi = d + g          # 改进后最长弹跳距离
    m = len(xs)
    f = [NEG] * m
    f[0] = 0                    # 虚拟起点：位于 0，分数 0
    dq: deque[int] = deque()    # 窗内下标按 f 递减，队首就是窗内最高分
    r = -1                      # 已入队的最右下标；-1 表示虚拟起点还没入队
    for i in range(1, m):
        xi = xs[i]
        right = xi - lo         # 只有 xs[j] <= xi - lo 才跳得过来
        while r + 1 < m and xs[r + 1] <= right:
            r += 1
            while dq and f[dq[-1]] <= f[r]:  # 维持 f 单调递减
                dq.pop()
            dq.append(r)
        left = xi - hi          # xs[j] < xi - hi 的格子已经跳不到，出窗
        while dq and xs[dq[0]] < left:
            dq.popleft()
        f[i] = (f[dq[0]] if dq else NEG) + ss[i]  # 哨兵区加分数仍是哨兵区
        if f[i] >= k:           # 游戏可在任意格子结束，够分即可停
            return True
    return False


def min_coins(xs: list[int], ss: list[int], d: int, k: int) -> int:
    """二分最少金币数：正分总和不足 k 直接无解，否则在「依次访问全部正格」的上界内二分。"""
    pos_sum = sum(s for s in ss if s > 0)  # 只访问正格、跳过负格的最高分
    if pos_sum < k:
        return -1

    # 上界：依次访问所有正格时，g 要让 [max(1, d-g), d+g] 盖住起点到各正格的每个间隔
    prev, max_gap = 0, 0
    for i, s in enumerate(ss):
        if s > 0:
            max_gap = max(max_gap, xs[i] - prev)
            prev = xs[i]
    lo_g, hi_g = 0, max(d - 1, max_gap - d)  # d-1 让下界缩到 1，max_gap-d 让上界够长

    while lo_g < hi_g:
        mid = (lo_g + hi_g) // 2
        if check(mid, xs, ss, d, k):
            hi_g = mid
        else:
            lo_g = mid + 1
    return lo_g


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, d, k = next(data), next(data), next(data)
    xs, ss = [0], [0]
    for _ in range(n):
        x = next(data)
        s = next(data)
        xs.append(x)
        ss.append(s)
    print(min_coins(xs, ss, d, k))


if __name__ == "__main__":
    solve()
