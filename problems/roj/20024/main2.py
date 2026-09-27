#!/usr/bin/env python3
"""ROJ 20024《棋》：优先讲清思想的五列窗口 DP。

写法兼容 Python 3.15。它省去了染色标记，容易理解，但运行速度较慢。
"""

NONE = 8          # 棋盘外的虚拟列；状态里写成 None，编成整数时才变成 8
NEG = -10**100


def get_color(pattern: int, row: int) -> int:
    """一列用 3 bit 表示；第 row 位是 0 表示 O，是 1 表示 X。"""
    return pattern >> row & 1


# 窗口是 3 行 x 5 列。长度为 3 的直线有很多条，但本轮只结算中间列（列 2），
# 所以只保留"经过列 2"的线。每条线写成 3 个 (行, 列) 格子，行取 0..2，列取 0..4：
#
#        列 0   列 1   列 2   列 3   列 4
#   行 0   .      .      .      .      .
#   行 1   .      .      .      .      .
#   行 2   .      .      .      .      .
#                 ↑ 中间列，本轮的结算对象
def build_lines():
    """生成 3 行 x 5 列窗口里所有经过中间列的三连，共 16 条。"""
    lines = []

    # 横向 9 条：每行都有 3 条（起点列 0 / 1 / 2），条条都经过列 2，生成：
    #   ((0,0),(0,1),(0,2))  ((0,1),(0,2),(0,3))  ((0,2),(0,3),(0,4))
    #   ((1,0),(1,1),(1,2))  ((1,1),(1,2),(1,3))  ((1,2),(1,3),(1,4))
    #   ((2,0),(2,1),(2,2))  ((2,1),(2,2),(2,3))  ((2,2),(2,3),(2,4))
    for r in range(3):
        for c in range(3):
            lines.append(((r, c), (r, c + 1), (r, c + 2)))

    # 纵向 1 条：只有列 2 自己的竖线完整落在窗口里，生成：
    #   ((0,2),(1,2),(2,2))
    lines.append(((0, 2), (1, 2), (2, 2)))

    # 右下斜 3 条：从第 0 行走到第 2 行，行 +1、列 +1，生成：
    #   ((0,0),(1,1),(2,2))  ((0,1),(1,2),(2,3))  ((0,2),(1,3),(2,4))
    for c in range(3):
        lines.append(((0, c), (1, c + 1), (2, c + 2)))

    # 右上斜 3 条：从第 0 行走到第 2 行，行 +1、列 -1，生成：
    #   ((0,2),(1,1),(2,0))  ((0,3),(1,2),(2,1))  ((0,4),(1,3),(2,2))
    for c in range(3):
        lines.append(((0, c + 2), (1, c + 1), (2, c)))

    return tuple(lines)


LINES = build_lines()


def colored_mask(window) -> int:
    """窗口中间列哪几行位于某个三连中：第 row 位为 1 表示 (row, 2) 被染色。"""
    mask = 0

    for cells in LINES:
        # 三连里只要有一格是虚拟列（棋盘外），这条线就不成立
        if any(window[c] is None for _, c in cells):
            continue

        # 三个格子同色，才构成一条三连
        r0, c0 = cells[0]
        color = get_color(window[c0], r0)
        if not all(get_color(window[c], r) == color for r, c in cells):
            continue

        # 只登记中间列的行
        for r, c in cells:
            if c == 2:
                mask |= 1 << r

    return mask


def window_code(window) -> int:
    """5 列窗口 -> 9 进制整数（window[0] 是最高位，window[4] 是最低位）。"""
    code = 0
    for pattern in window:
        code = code * 9 + (NONE if pattern is None else pattern)
    return code


def decode_window(code):
    """9 进制整数 -> 5 列窗口，是 window_code 的逆运算。"""
    window = [None] * 5
    for i in range(4, -1, -1):      # window[4] 是最低位
        p = code % 9
        window[i] = None if p == NONE else p
        code //= 9
    return window


# 预处理：窗口一共 9^5 种，每种窗口"中间列哪几行被染色"先整表算好。
# 主循环里同一个窗口会反复出现，查表比每次重判 16 条三连省事得多。
COLORED = bytearray(9 ** 5)
for _code in range(9 ** 5):
    COLORED[_code] = colored_mask(decode_window(_code))


def middle_score(window, col: int, weight: list[list[int]]) -> int:
    """五列都已知时，计算正中间这一列的完整得分。"""
    mask = COLORED[window_code(window)]
    pattern = window[2]
    score = 0

    for row in range(3):
        if mask >> row & 1:
            sign = 1 if get_color(pattern, row) == 1 else -1
            score += sign * weight[row][col]

    return score


def solve() -> None:
    n = int(input())
    weight = [list(map(int, input().split())) for _ in range(3)]

    # 状态是最近至多四列的图案，值是已经结算的最大得分。
    # 开头先放两个 None，表示棋盘左边的两列不存在。
    dp = {(None, None): 0}

    # 枚举 n 列真实棋盘，再补两个 None，让最后两列也能成为窗口中心。
    for next_col in range(n + 2):
        choices = range(8) if next_col < n else (None,)
        next_dp = {}

        for state, old_score in dp.items():
            for pattern in choices:
                window = state + (pattern,)
                gain = 0

                # 凑齐五列后，中间列左右各有两列，它的颜色已经完全确定。
                if len(window) == 5:
                    middle_col = next_col - 2
                    gain = middle_score(window, middle_col, weight)

                new_state = window[-4:]
                new_score = old_score + gain
                next_dp[new_state] = max(next_dp.get(new_state, NEG), new_score)

        dp = next_dp

    print(max(dp.values()))


if __name__ == "__main__":
    solve()
