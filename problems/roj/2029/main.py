#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:44
# update_at: 2026-10-01 03:44

import sys
from collections.abc import Iterator
from itertools import product

# 同一个按钮按两次等于没按，所以每个按钮只需考虑按 0/1 次，共 16 种奇偶组合；
# 又因奇数灯归按钮 2、偶数灯归按钮 3、3k+1 灯归按钮 4，各按钮的覆盖范围
# 以 6 为周期重复，所以整个结局只由"前 6 盏灯的翻转图案 + 总按压次数的奇偶"决定。
BUTTONS = tuple(product((0, 1), repeat=4))  # (按钮1, 按钮2, 按钮3, 按钮4) 各按 0/1 次


def flip_pattern(presses: tuple[int, ...]) -> int:
    """一组按钮奇偶对前 6 盏灯的翻转图案：第 k 位为 1 表示第 k+1 盏灯被翻转。"""
    p1, p2, p3, p4 = presses
    mask = 0
    for k in range(6):
        # 灯 k+1 受按钮 2/3 之一（看灯号奇偶）与按钮 4（灯号是 3k+1）共同作用
        if p1 ^ (p2 if k % 2 == 0 else p3) ^ (p4 if k % 3 == 0 else 0):
            mask |= 1 << k
    return mask


# 16 种奇偶组合的图案两两不同（由图案可反解出 p2、p3、p4 和 p1），
# 于是每种图案对应唯一的最少按压次数 = 四个按钮按压次数之和。
STATES = sorted((sum(presses), flip_pattern(presses)) for presses in BUTTONS)


def lamp_set(tokens: Iterator[int]) -> set[int]:
    """读到哨兵 -1 为止的一组灯号。"""
    lamps: set[int] = set()
    while (lamp := next(tokens)) != -1:
        lamps.add(lamp)
    return lamps


def lamp_state(pattern: int, lamp: int) -> int:
    """灯 lamp 的最终状态：初始全亮，被翻转过则变 0。"""
    return 1 ^ (pattern >> (lamp - 1) % 6 & 1)


def solve() -> None:
    tokens = iter(map(int, sys.stdin.buffer.read().split()))
    n, c = next(tokens), next(tokens)
    on, off = lamp_set(tokens), lamp_set(tokens)

    rows = sorted({
        ''.join(str(lamp_state(pattern, lamp)) for lamp in range(1, n + 1))
        for min_press, pattern in STATES
        # 恰好按 c 次：先够到最少次数，剩下的次数两两成对补进任意按钮
        if min_press <= c and (c - min_press) % 2 == 0
        # 亮灯与灭灯约束全部满足
        if all(lamp_state(pattern, lamp) == 1 for lamp in on)
        if all(lamp_state(pattern, lamp) == 0 for lamp in off)
    })
    print('\n'.join(rows) if rows else 'IMPOSSIBLE')


if __name__ == "__main__":
    solve()
