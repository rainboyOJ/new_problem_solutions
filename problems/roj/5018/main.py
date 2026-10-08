#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 20:00
# update_at: 2026-10-08 20:00

import sys
from heapq import heappush, heappop

# 每项工作编码成 (截止时刻 d_i = M - C_i, 净支出 p_i = D_i - C_i)
type Jobs = list[tuple[int, int]]


def max_jobs(jobs: Jobs) -> int:
    """反悔贪心解单机 1||ΣU_j：按截止时刻升序接工作，超时则退掉净支出最大的一项。"""
    used = 0                 # 已接工作的总净支出
    chosen: list[int] = []   # 已接工作的净支出取负入堆 => 小根堆当大根堆用
    for deadline, cost in jobs:
        used += cost
        heappush(chosen, -cost)
        if used > deadline:
            dropped = heappop(chosen)  # 堆里是负数，加回 used 等于退掉该项的净支出
            used += dropped
    return len(chosen)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)

    spend = [next(data) for _ in range(n)]   # 题面的 D_i
    reward = [next(data) for _ in range(n)]  # 题面的 C_i

    # 做第 i 项工作前需要手上钱 >= D_i，即此前总净支出 <= M - D_i，
    # 等价于"必须在时刻 d_i = M - C_i 前完成处理时间为 p_i 的工作"。
    # EDD（按 d_i 升序，即 C_i 降序）是"该集合能被完成"的充分顺序。
    jobs: Jobs = sorted((m - c, d - c) for d, c in zip(spend, reward))

    print(max_jobs(jobs))


if __name__ == "__main__":
    solve()
