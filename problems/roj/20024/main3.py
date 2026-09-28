#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-28 12:53
# update_at: 2026-09-28 16:58

import sys
from collections.abc import Iterable
from functools import cache

NEG = -10**100


def get_color(pattern: int, row: int) -> int:
    """取一列第 row 位的颜色：0 表示 O，1 表示 X。"""
    return pattern >> row & 1


# 窗口里所有"经过中间列（列 2）"的三连，共 16 条；每条写成 3 个 (行, 列) 格子。
# 本轮只结算中间列，所以别的线一概不要。
LINES = (
    [((r, c), (r, c + 1), (r, c + 2)) for r in range(3) for c in range(3)]  # 横向 9 条
    + [((0, 2), (1, 2), (2, 2))]                                           # 纵向 1 条
    + [((0, c), (1, c + 1), (2, c + 2)) for c in range(3)]                  # 右下斜 3 条
    + [((0, c + 2), (1, c + 1), (2, c)) for c in range(3)]                  # 右上斜 3 条
)


@cache
def colored_mask(window: tuple[int | None, ...]) -> int:
    """窗口中间列哪几行位于某个三连中：第 row 位为 1 表示 (row, 2) 被染色。

    窗口是元组（元素为 0..7 或 None），天然可哈希，所以能直接当缓存键：
    同一个窗口只算一次，效果和 main2.py 里那张 COLORED 表一样，但按需生成。
    """
    mask = 0
    for cells in LINES:
        if any(window[c] is None for _, c in cells):
            continue                                    # 有格子落在棋盘外
        if len({get_color(window[c], r) for r, c in cells}) == 1:  # 三格同色
            mask |= sum(1 << r for r, c in cells if c == 2)        # 只登记中间列
    return mask


def middle_score(window: tuple[int | None, ...], col: int, weight: list[list[int]]) -> int:
    """五列都已知时，计算正中间那一列（棋盘第 col 列）的完整得分。"""
    mask = colored_mask(window)
    middle = window[2]                                       # 窗口五列里结算的就是第 2 列
    return sum(
        (1 if get_color(middle, r) else -1) * weight[r][col]  # X 红 +，O 蓝 -
        for r in range(3)
        if mask >> r & 1
    )


def advance(dp: dict[tuple[int | None, ...], int], choices: Iterable[int | None],
            col: int, weight: list[list[int]]) -> dict[tuple[int | None, ...], int]:
    """滑动一列：每个旧状态接上新列的图案，凑满五列时就结算窗口中心那一列。"""
    nxt: dict[tuple[int | None, ...], int] = {}
    for state, score in dp.items():
        for pattern in choices:
            window = state + (pattern,)
            gain = middle_score(window, col, weight) if len(window) == 5 else 0
            new_state = window[-4:]                          # 只留最近 4 列当下一轮的状态
            nxt[new_state] = max(nxt.get(new_state, NEG), score + gain)
    return nxt


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    weight = [[next(data) for _ in range(n)] for _ in range(3)]

    # 状态是最近至多 4 列的图案。左侧两列在棋盘外，先垫两个 None 当窗口左边界，
    # 这样第 0 列会在 next_col = 2 时正好落到窗口中心被结算。
    dp: dict[tuple[int | None, ...], int] = {(None, None): 0}

    for next_col in range(n + 2):
        # 棋盘内的列有 8 种图案；末尾追加两个 None，把最后两列也顶到窗口中心。
        choices = range(8) if next_col < n else (None,)
        dp = advance(dp, choices, next_col - 2, weight)

    # 补的 None 已经把每一列都结算过，剩下的状态只比总分。
    print(max(dp.values()))


if __name__ == "__main__":
    solve()
