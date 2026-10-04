#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 20:00
# update_at: 2026-10-02 20:00

import sys
from bisect import bisect_right
from itertools import accumulate

INF = 10**30  # 不可达哨兵：真实代价上限约 1e18，远小于它


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, v, s = next(data), next(data), next(data)
    cust = [(next(data), next(data), next(data)) for _ in range(n)]  # (p, A, d)
    sum_a = sum(a for _, a, _ in cust)  # A 与路线无关，直接累加

    # 把起点当 d=A=0 的虚拟客户并入，只按位置排序（稳定），虚拟点排在同位置组末尾
    pts = sorted(cust + [(s, 0, 0)], key=lambda e: e[0])
    m = n + 1
    x = [p for p, _, _ in pts]
    d = [dd for _, _, dd in pts]
    pref = list(accumulate(d, initial=0))  # pref[i] = 前 i 个点的 d 之和
    total_d = pref[m]
    si = bisect_right(x, s) - 1  # 虚拟起点下标：最后一个位置为 s 的点

    # 区间 DP：状态 (l, r, 端点) = 已送完连续区间 [l, r]、无人机停在端点。
    # 每次只向外扩展一位，代价 = 扩展前未送客户的 d 和 × 距离 / v（全部 d 在飞行期间同时增长）。
    # 所有除法分母都是同一个 v，故整条路线只在最后除一次 v，途中全用整数分子，避免浮点误差。
    # 转移只依赖宽度 w-1 的层，滚动数组即可，空间 O(n)。
    prev_l = [INF] * (m + 2)
    prev_r = [INF] * (m + 2)
    prev_l[si] = prev_r[si] = 0  # 起点即初始区间，尚未移动，代价为 0
    for w in range(1, m):  # 按区间宽度从小到大推进
        lo, hi = max(0, si - w), min(si, m - 1 - w)  # 保证区间包含 si
        cur_l = [INF] * (m + 2)
        cur_r = [INF] * (m + 2)
        for l in range(lo, hi + 1):
            r = l + w
            if l < si:  # 从 [l+1, r] 向左送第 l 个客户，无人机停在左端
                seg = total_d - (pref[r + 1] - pref[l + 1])  # 扩展前未送名单的 d 和
                cur_l[l] = min(
                    prev_l[l + 1] + seg * abs(x[l + 1] - x[l]),  # 原来停在左端
                    prev_r[l + 1] + seg * abs(x[r] - x[l]),  # 原来停在右端，横穿已送区间
                )
            if r > si:  # 从 [l, r-1] 向右送第 r 个客户，无人机停在右端
                seg = total_d - (pref[r] - pref[l])
                cur_r[l] = min(
                    prev_l[l] + seg * abs(x[l] - x[r]),
                    prev_r[l] + seg * abs(x[r - 1] - x[r]),
                )
        prev_l, prev_r = cur_l, cur_r

    # 全部客户送完 = 区间 [0, m-1]；分子 ÷ v 后向下取整再加常数 A
    print(sum_a + min(prev_l[0], prev_r[0]) // v)


if __name__ == "__main__":
    solve()
