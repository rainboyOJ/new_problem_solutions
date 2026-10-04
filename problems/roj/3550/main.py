#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:54
# update_at: 2026-10-02 06:54

import sys
from bisect import insort


def earliest_slot(intervals: list[tuple[int, int]], release: int, dur: int) -> int:
    """在机器已占用的区间（按 start 升序）中，找到能放下长度 dur 任务的最早开始时刻。

    从左往右扫描相邻区间之间的空档 [prev_end, s]：开始时刻不得早于 release，
    只要 start + dur 不越过下一个区间的 start，这个空档就是"最前面的空档"。
    """
    prev_end = 0
    for s, e in intervals:
        start = max(prev_end, release)  # 受工件释放时刻与空档左端双重约束
        if start + dur <= s:
            return start
        prev_end = e
    return max(prev_end, release)       # 机器末尾的空档一定能放下


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)                # m 台机器，n 个工件

    order = [next(data) for _ in range(n * m)]   # 安排顺序：展开后的工件号序列

    # mach[j][k] / cost[j][k]：工件 j 第 k 道工序的机器号与加工时间（1-based，第 0 行为哨兵）
    mach = [[0] * (m + 1)] + [[0] + [next(data) for _ in range(m)] for _ in range(n)]
    cost = [[0] * (m + 1)] + [[0] + [next(data) for _ in range(m)] for _ in range(n)]

    step = [0] * (n + 1)      # 工件 j 已安排的工序数（即下一道是第 step+1 道）
    job_free = [0] * (n + 1)  # 工件 j 当前最后一个操作的完成时刻
    slots: list[list[tuple[int, int]]] = [[] for _ in range(m + 1)]  # 每台机器的占用区间

    for j in order:  # 按给定顺序逐个安排操作，已安排的不动
        step[j] += 1
        k = step[j]                              # 该工件轮到第 k 道工序
        machine, dur = mach[j][k], cost[j][k]
        start = earliest_slot(slots[machine], job_free[j], dur)
        insort(slots[machine], (start, start + dur))  # 新区间保持有序
        job_free[j] = start + dur

    print(max(job_free))  # 某个工件最后一道工序的完成时刻即总时间


if __name__ == "__main__":
    solve()
