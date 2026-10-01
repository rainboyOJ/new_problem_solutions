#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:19
# update_at: 2026-10-01 09:19

import sys

ALL_LIGHTS = 0b11111  # 5 盏灯全亮的状态编码：低 5 位全为 1
INF = 100             # 哨兵：表示在步数限制内不可行


def simulate_first_row(grid: list[int], op0: int) -> int:
    """给定第一行的操作方案 op0，递推后续各行并返回使全部灯变亮所需的最少步数。"""
    rows = list(grid)
    press_count = 0

    # 第一行执行 op0
    curr_op = op0
    for r in range(5):
        press_count += curr_op.bit_count()
        if press_count > 6:
            return INF
        # 当前行自身及左右受 curr_op 影响
        rows[r] ^= curr_op ^ ((curr_op << 1) & ALL_LIGHTS) ^ (curr_op >> 1)
        # 下一行受影响
        if r + 1 < 5:
            rows[r + 1] ^= curr_op
            # 下一行的操作完全由当前行未亮的灯唯一确定
            curr_op = (~rows[r]) & ALL_LIGHTS
        else:
            # 最后一行已无下一行可操作，若仍有灯未亮则该方案不合法
            if rows[r] != ALL_LIGHTS:
                return INF

    return press_count


def min_steps_for_board(grid: list[int]) -> int:
    """枚举第一行的所有 32 种按键可能，返回 <= 6 的最少步数；若无法达成返回 -1。"""
    best = min((simulate_first_row(grid, op) for op in range(32)), default=INF)
    return best if best <= 6 else -1


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    idx = 1
    out: list[int] = []

    for _ in range(n):
        # 每行 5 个字符转为 5 位二进制整数（第 c 位对应列 c）
        grid = [
            sum((int(ch) << c) for c, ch in enumerate(data[idx + r]))
            for r in range(5)
        ]
        idx += 5
        out.append(min_steps_for_board(grid))

    print('\n'.join(map(str, out)))


if __name__ == "__main__":
    solve()
