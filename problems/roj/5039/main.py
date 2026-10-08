#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:53
# update_at: 2026-10-08 23:06

import sys


def solve() -> None:
    """模拟出圈：每轮在剩余人员上前进 m-1 步定出圈者，环形回绕用取模。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)  # 题面保证 2 <= n, m <= 1000，单组输入

    people = list(range(1, n + 1))  # people 始终是"尚未出圈的人"的编号列表
    idx = 0                         # 本轮报数起点的下标，初始从第 1 个人开始
    order: list[int] = []
    while people:
        idx = (idx + m - 1) % len(people)  # 数到第 m 个的人出圈
        order.append(people.pop(idx))      # 出圈者位置被后一个人顶替，idx 即下轮起点

    print(' '.join(map(str, order)))


if __name__ == "__main__":
    solve()
