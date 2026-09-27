#!/usr/bin/env python3
"""ROJ 20024《棋》：优先讲清思想的五列窗口 DP。

写法兼容 Python 3.15。它省去了染色标记，容易理解，但运行速度较慢。
"""


# 横、竖、右下斜、右上斜四个方向。
DIRECTIONS = ((0, 1), (1, 0), (1, 1), (1, -1))
NEG = -10**100


def get_color(pattern: int, row: int) -> int:
    """一列用 3 bit 表示；第 row 位是 0 表示 O，是 1 表示 X。"""
    return pattern >> row & 1


def is_colored(window, row: int) -> bool:
    """判断五列窗口正中间的 (row, 2) 是否位于某个三连中。"""
    target = get_color(window[2], row)

    for dr, dc in DIRECTIONS:
        # 当前格可以是三连中的第 0、1、2 个格子。
        for position in range(3):
            same = True

            for k in range(3):
                r = row + (k - position) * dr
                c = 2 + (k - position) * dc

                if not (0 <= r < 3 and 0 <= c < 5):
                    same = False
                    break
                if window[c] is None:  # None 表示棋盘外的虚拟列
                    same = False
                    break
                if get_color(window[c], r) != target:
                    same = False
                    break

            if same:
                return True

    return False


def middle_score(window, col: int, weight: list[list[int]]) -> int:
    """五列都已知时，计算正中间这一列的完整得分。"""
    pattern = window[2]
    score = 0

    for row in range(3):
        if is_colored(window, row):
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
