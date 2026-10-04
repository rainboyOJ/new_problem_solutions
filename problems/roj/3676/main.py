#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 15:04
# update_at: 2026-10-02 15:04

import sys

DIALS = 5  # 拨圈数


def predecessors(state: tuple[int, ...]) -> set[tuple[int, ...]]:
    """一次合法转动恰好到达 state 的全部密码：5×9 个单拨圈 + 4×9 个相邻双拨圈。"""
    # 单拨圈反推：任一拨圈换成另外 9 个数字之一（幅度非零）
    single = {
        state[:i] + (v,) + state[i + 1:]
        for i in range(DIALS)
        for v in range(10)
        if v != state[i]
    }
    # 相邻双拨圈反推：两位同时减同一个非零幅度 d（模 10 循环）
    pair = {
        state[:i] + ((state[i] - d) % 10, (state[i + 1] - d) % 10) + state[i + 2:]
        for i in range(DIALS - 1)
        for d in range(1, 10)
    }
    return single | pair


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    states = [tuple(next(data) for _ in range(DIALS)) for _ in range(n)]

    # 正确密码必须同时是每个状态的前驱，取交集即得答案
    cand = predecessors(states[0])
    for state in states[1:]:
        cand &= predecessors(state)

    print(len(cand))


if __name__ == "__main__":
    solve()
