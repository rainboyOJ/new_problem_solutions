#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 21:16
# update_at: 2026-09-30 21:35

import sys
from collections import deque
from collections.abc import Callable


def window_best(seq: list[int], k: int, pick: Callable[[int, int], int]) -> list[int]:
    """长度 k 的滑动窗口逐个求最值：pick 传 min 或 max，产出 len(seq)-k+1 个结果。"""
    dq: deque[int] = deque()  # 存下标，对应值按 pick 单调，队首下标就是窗口最值
    best: list[int] = []
    for i, value in enumerate(seq):
        while dq and pick(seq[dq[-1]], value) == value:
            dq.pop()  # 新值更优（或相等且更靠右），旧队尾永远轮不上
        dq.append(i)
        if dq[0] <= i - k:
            dq.popleft()  # 队首已滑出窗口
        if i >= k - 1:
            best.append(seq[dq[0]])
    return best


def solve() -> None:
    header = iter(map(int, sys.stdin.buffer.readline().split()))
    row_count, col_count, side = next(header), next(header), next(header)  # a, b, n

    # 横向：逐行读入立即压成两张行窗口表，原矩阵不整体驻留内存
    row_min: list[list[int]] = []
    row_max: list[list[int]] = []
    for _ in range(row_count):
        row = list(map(int, sys.stdin.buffer.readline().split()))
        row_min.append(window_best(row, side, min))
        row_max.append(window_best(row, side, max))

    # 纵向：行窗口表第 c 列再滑一次；min/max 各自两遍复合正是 n×n 方格的最值。
    # 方格差值上界 1e9，先给大数作初始答案再逐格收紧。
    ans = 10**18
    for c in range(col_count - side + 1):
        col_min = window_best([row_min[r][c] for r in range(row_count)], side, min)
        col_max = window_best([row_max[r][c] for r in range(row_count)], side, max)
        for square_min, square_max in zip(col_min, col_max):
            ans = min(ans, square_max - square_min)

    print(ans)


if __name__ == "__main__":
    solve()
