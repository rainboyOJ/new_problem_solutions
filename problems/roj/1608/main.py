#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:49
# update_at: 2026-09-30 21:49

import re
import sys
from itertools import accumulate

# 01~06 过程见 problem-analysis-workspace/；核心推导：
# 把每批启动费 S 改记为"批次开始时对之后所有任务的费用系数付费"（S*(总C - 前缀C_j)），
# 交叉项只剩 -sum_t[i]*sum_c[j]，DP 变成在直线族 y = -sum_c[j]*x + f[j] 上、
# 取 x = sum_t[i] + S 处的最小值 —— 斜率随 j 单调不增，可维护下凸壳。


def crossing(left: tuple[int, int], right: tuple[int, int]) -> tuple[int, int]:
    """两条直线交点的分数 (分子, 分母)，分母 > 0；交点右侧斜率小的那条更优。"""
    (m1, b1), (m2, b2) = left, right
    return b2 - b1, m1 - m2


def hull_push(ms: list[int], bs: list[int], thr: list[tuple[int, int]], m: int, b: int) -> None:
    """斜率单调不增地插入直线 y = m*x + b，删掉尾部从此取不到最小值的直线。"""
    while ms and m == ms[-1]:  # 同斜率只留截距小的，新直线处处不更优就直接丢弃
        if b >= bs[-1]:
            return
        ms.pop()
        bs.pop()
        if thr:
            thr.pop()

    # 交点必须严格递增，否则夹在中间的直线在任何 x 处都轮不到
    while len(ms) >= 2:
        n1, d1 = crossing((ms[-2], bs[-2]), (ms[-1], bs[-1]))
        n2, d2 = crossing((ms[-1], bs[-1]), (m, b))
        if n1 * d2 < n2 * d1:  # 分数比较：交点左移说明中间直线是废的
            break
        ms.pop()
        bs.pop()
        thr.pop()

    if ms:
        thr.append(crossing((ms[-1], bs[-1]), (m, b)))
    ms.append(m)
    bs.append(b)


def hull_min(ms: list[int], bs: list[int], thr: list[tuple[int, int]], x: int) -> int:
    """在下凸壳上二分：找到第一条 x 尚未越过其交点的直线，返回它在 x 处的值。"""
    lo, hi = 0, len(thr)
    while lo < hi:
        mid = (lo + hi) >> 1
        num, den = thr[mid]
        if x * den > num:  # x 已经越过交点，右边的直线更优
            lo = mid + 1
        else:
            hi = mid
    # lo 越过全部交点时正好等于最后一段直线的下标（len(thr) == len(ms) - 1）
    return ms[lo] * x + bs[lo]


def solve() -> None:
    nums = list(map(int, re.findall(rb'-?\d+', sys.stdin.buffer.read())))
    n, setup = nums[0], nums[1]
    ts = nums[2::2][:n]
    cs = nums[3::2][:n]

    sum_t = list(accumulate(ts, initial=0))  # 任务用时前缀和
    sum_c = list(accumulate(cs, initial=0))  # 费用系数前缀和，同时充当直线斜率
    tail_c = sum_c[-1]

    ms = [0]  # 直线族先放 j = 0：斜率 -sum_c[0] = 0
    bs = [0]  # 截距 f[0] = 0
    thr: list[tuple[int, int]] = []
    f = 0

    for i in range(1, n + 1):
        x = sum_t[i] + setup  # 查询点：前缀用时 + 启动费
        f = sum_t[i] * sum_c[i] + setup * tail_c + hull_min(ms, bs, thr, x)
        hull_push(ms, bs, thr, -sum_c[i], f)

    print(f)


if __name__ == "__main__":
    solve()
