#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:50
# update_at: 2026-09-30 21:50

import sys
from collections import deque
from itertools import accumulate


def min_cost(startup: int, pre_t: list[int], pre_c: list[int]) -> int:
    """前 n 个任务分批的最小总费用 f[n]（斜率优化，O(n)）。

    换记账次序后 f[i] = min_j { f[j] + (startup + pre_t[i]-pre_t[j]) × (pre_c[n]-pre_c[j]) }，
    把与 j 有关的量收成点 (pre_c[j], y[j])、与 i 有关的收成斜率 k = pre_t[i]，
    转移变成"用斜率 k 的直线去切下凸壳"，取 f[i] = k×pre_c[n] + min_j { y[j] - k×pre_c[j] }。
    T_i, C_i 均为正，pre_t 与 pre_c 严格递增，故查询斜率与插入横坐标都单调：
    队头弹出比不过的决策、队尾弹出破坏凸性的决策，每个决策进出队各一次。
    """
    n = len(pre_t) - 1
    total_c = pre_c[n]
    f = [0] * (n + 1)
    y = [0] * (n + 1)
    y[0] = startup * total_c  # j = 0 处的截距：f[0] - pre_t[0]×(total_c-pre_c[0]) + startup×total_c

    hull = deque([0])  # 下凸壳上决策点的编号，pre_c[j] 随入队单调递增
    for i in range(1, n + 1):
        k = pre_t[i]  # 本轮查询斜率，随 i 单调递增
        while len(hull) >= 2 and y[hull[0]] - k * pre_c[hull[0]] >= y[hull[1]] - k * pre_c[hull[1]]:
            hull.popleft()  # 队头不如次队头，且后面的 k 只会更大，此后再也用不到
        j = hull[0]  # 最优切点：使 f[i] 最小的那一段左边界
        f[i] = k * total_c + y[j] - k * pre_c[j]
        y[i] = f[i] - pre_t[i] * (total_c - pre_c[i]) + startup * (total_c - pre_c[i])
        while len(hull) >= 2:
            a, b = hull[-2], hull[-1]
            slope_ab = (y[b] - y[a]) * (pre_c[i] - pre_c[b])   # 叉积比较代替除法，避免精度
            slope_bi = (y[i] - y[b]) * (pre_c[b] - pre_c[a])
            if slope_ab >= slope_bi:
                hull.pop()  # b 被线段 a-i 盖住，不再在凸壳上
            else:
                break
        hull.append(i)
    return f[n]


def solve() -> None:
    nums = list(map(int, sys.stdin.buffer.read().split()))
    n, startup = nums[0], nums[1]  # 任务数 n、每批启动时间 S
    times = nums[2:2 + 2 * n:2]    # 各任务耗时 T_i，共 n 个
    fees = nums[3:2 + 2 * n:2]     # 各任务费用系数 C_i，共 n 个
    pre_t = list(accumulate(times, initial=0))  # n+1 个前缀和，下标 0 处为 0
    pre_c = list(accumulate(fees, initial=0))
    print(min_cost(startup, pre_t, pre_c))


if __name__ == "__main__":
    solve()
