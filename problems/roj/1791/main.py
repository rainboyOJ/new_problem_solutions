#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:16
# update_at: 2026-10-08 03:16

import sys

INF = 4 * 10**18  # 上界：S <= 3e8 时 Σs_i^2 <= S^2 <= 9e16

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Hull = list[tuple[int, int]]  # 下凸壳上的直线 y = m*x + b，斜率随下标严格递减


def hull_add(hull: Hull, m: int, b: int) -> None:
    """按斜率递减的顺序加入直线 y = m*x + b，弹掉被两头夹住、永不最优的中间线。"""
    while len(hull) >= 2:
        m1, b1 = hull[-2]
        m2, b2 = hull[-1]
        # line2 与 new 的交点不晚于 line1 与 line2 的交点 => line2 不在包上
        if (b - b1) * (m1 - m2) <= (b2 - b1) * (m1 - m):
            hull.pop()
        else:
            break
    hull.append((m, b))


def solve_ring_small(ring: list[int], n: int, k: int) -> int:
    """n <= 400：枚举 n 个断环起点，每层做单调凸包优化的 DP，求最小 Σs_i^2。

    dp[i] = 前 i 个点分成当前层数的最小 Σs^2，转移 dp[i] = min_j dp[j] + (cur[i]-cur[j])^2；
    展开得 cur[i]^2 + min_j ( -2*cur[j]*cur[i] + dp[j]+cur[j]^2 )，括号里是 x = cur[i] 处
    一堆直线的最小值。x 单调不减、斜率 -2*cur[j] 单调递减，故查询指针只往右走，均摊 O(1)。
    """
    best = INF
    for d in range(n):
        cur = [0] * (n + 1)
        for i in range(1, n + 1):
            cur[i] = cur[i - 1] + ring[d + i - 1]  # 把环从 ring[d] 处断开后的前缀和

        dp = [INF] * (n + 1)
        dp[0] = 0
        for _ in range(k):
            hull: Hull = []
            ptr = 0      # 当前 x 所对应的最优直线下标，随 x 增大只增不减
            ndp = [INF] * (n + 1)
            for i in range(1, n + 1):
                j = i - 1
                if dp[j] < INF:
                    hull_add(hull, -2 * cur[j], dp[j] + cur[j] * cur[j])
                if hull:
                    x = cur[i]
                    if ptr >= len(hull):
                        ptr = len(hull) - 1
                    while ptr + 1 < len(hull) and (
                        hull[ptr + 1][0] * x + hull[ptr + 1][1]
                        <= hull[ptr][0] * x + hull[ptr][1]
                    ):
                        ptr += 1
                    ndp[i] = hull[ptr][0] * x + hull[ptr][1] + x * x
            dp = ndp
        best = min(best, dp[n])
    return best


def solve_ring_k2(pre: list[int], n: int, s: int) -> int:
    """n 大且 K=2：双指针维护权和最接近 S/2 的切点，O(n)。"""
    best = INF
    j = 1
    for i in range(1, n + 1):
        while j <= i + n - 2 and (pre[j + 1] - pre[i - 1]) * 2 <= s:
            j += 1
        for cut in (j, j + 1):  # S/2 两侧各取一个切点
            if cut < i or cut > i + n - 1:
                continue
            v = pre[cut] - pre[i - 1]
            best = min(best, v * v + (s - v) * (s - v))
    return best


def solve_ring_k3(pre: list[int], n: int, s: int) -> int:
    """n 大且 K=3：第一个切点取权和 <= S/3 的最远点，第二个切点用单调指针定位，O(n)。"""
    best = INF
    j = 1
    l = 1
    for i in range(1, n + 1):
        while j <= i + n - 2 and (pre[j + 1] - pre[i - 1]) * 3 <= s:
            j += 1
        l = max(l, j + 1)  # 第二段必须非空；j 递增 => 目标权和递增 => l 也单调不减
        while l + 1 <= i + n - 1 and (pre[l + 1] - pre[j]) * 3 <= s:
            l += 1
        for k2 in (l - 1, l, l + 1):  # 第二段权和在 S/3 两侧的候选
            if k2 < j + 1 or k2 > i + n - 2:
                continue
            v1 = pre[j] - pre[i - 1]
            v2 = pre[k2] - pre[j]
            v3 = s - v1 - v2
            if v3 > 0:
                best = min(best, v1 * v1 + v2 * v2 + v3 * v3)
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    a = [next(data) for _ in range(n)]

    ring = a + a  # 倍长，供断环起点与任意区间和取用
    pre = [0] * (2 * n + 1)
    for i in range(1, 2 * n + 1):
        pre[i] = pre[i - 1] + ring[i - 1]
    s = pre[n]  # 总长度

    if k <= 1:  # 只有一段，方差恒为 0
        print(0)
        return

    if n <= 400:
        min_sum_sq = solve_ring_small(ring, n, k)
    elif k == 2:
        min_sum_sq = solve_ring_k2(pre, n, s)
    else:
        min_sum_sq = solve_ring_k3(pre, n, s)  # 大数据里 K 只可能是 3

    print(k * k * min_sum_sq - k * s * s)  # Python 整数无溢出，与 C++ 的 __int128 同义


if __name__ == "__main__":
    solve()
