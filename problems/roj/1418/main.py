#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:15
# update_at: 2026-10-07 15:15

import sys
from collections import deque


def last_monkey(step: list[int]) -> int:
    """把圆圈摊成队列模拟报数，返回最后剩下的猴子编号；step[i] 是 i 号猴子的 Xi。"""
    circle = deque(range(1, len(step)))  # 队首是本轮起点，队尾的下一位绕回队首
    target = step[1]                     # 本轮要数到的次数，由起点（队首）的 Xi 决定
    counted = 0                          # 本轮已经数了几只猴子
    while len(circle) > 1:
        counted += 1
        monkey = circle.popleft()
        if counted == target:            # 正好数到目标：这只猴子淘汰，不回队尾
            counted = 0
            target = step[circle[0]]     # 下一轮从它的下一位开始，次数换成新队首的 Xi
        else:
            circle.append(monkey)        # 没数到：排回队尾等下一轮
    return circle[0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    step = [0] + [next(data) for _ in range(n)]  # step[i] = Xi，下标从 1 开始对应猴子编号
    print(last_monkey(step))


if __name__ == "__main__":
    solve()
