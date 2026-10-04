#!/usr/bin/env python3
import sys

"""ROJ 20024《棋》的教学版状态压缩 DP。

代码重在描述“3 列滑动窗口 + 染色标记”的思想。
使用字典和四元组保存状态，写法直观，但常数较大，可能无法通过最严数据。
兼容 Python 3.15。
"""


# 三列窗口 A、B、C 中需要检查的 6 条三连。
# 每个格子写成 (行号, 列号)，列号 0/1/2 分别表示 A/B/C。
LINES = (
    ((0, 0), (1, 0), (2, 0)),  # A 列纵向
    ((0, 0), (0, 1), (0, 2)),  # 三条横向
    ((1, 0), (1, 1), (1, 2)),
    ((2, 0), (2, 1), (2, 2)),
    ((0, 0), (1, 1), (2, 2)),  # 对角线 ↘
    ((2, 0), (1, 1), (0, 2)),  # 对角线 ↗
)


def color(pattern: int, row: int) -> int:
    """返回一列第 row 格的棋子：0 表示 O，1 表示 X。"""
    return pattern >> row & 1


def score_sign(pattern: int, row: int) -> int:
    """X 染红贡献为正，O 染蓝贡献为负。"""
    return 1 if color(pattern, row) == 1 else -1


def move(
    col_a: int,
    patterns: tuple[int, int, int],
    mark_a: int,
    mark_b: int,
    weight: list[list[int]],
) -> tuple[int, int, int]:
    """检查窗口 (A, B, C)，结算 A 列，并返回 B、C 的新标记。

    mark 的第 r 位为 1，表示这一格已经确定会染色，但分数还在挂账。
    A 列马上离开窗口，所以本轮结算；B、C 只记录标记，留到以后结算。
    """
    gain = 0
    mark_c = 0

    # A 列中以前已经确定染色的格子，现在统一结算。
    for row in range(3):
        if mark_a >> row & 1:
            gain += weight[row][col_a] * score_sign(patterns[0], row)

    for line in LINES:
        three_colors = [color(patterns[col], row) for row, col in line]
        if not (three_colors[0] == three_colors[1] == three_colors[2]):
            continue

        # 这条线上三个格子都会染色。
        for row, col in line:
            if col == 0:
                # A 列直接计分；用 mark_a 防止一个格子被重复计算。
                if not (mark_a >> row & 1):
                    gain += weight[row][col_a] * score_sign(patterns[0], row)
                    mark_a |= 1 << row
            elif col == 1:
                mark_b |= 1 << row
            else:
                mark_c |= 1 << row

    return gain, mark_b, mark_c


def finish_column(
    col: int, pattern: int, mark: int, weight: list[list[int]]
) -> int:
    """收尾时结算最后两列：已有标记，再补上本列的纵向三连。"""
    if pattern == 0 or pattern == 7:  # OOO 或 XXX
        mark = 7

    gain = 0
    for row in range(3):
        if mark >> row & 1:
            gain += weight[row][col] * score_sign(pattern, row)
    return gain


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    weight = [[next(data) for _ in range(n)] for _ in range(3)]

    # 少于 3 列时只有纵向三连，每列独立选择 XXX 或 OOO。
    if n <= 2:
        answer = 0
        for col in range(n):
            column_sum = sum(weight[row][col] for row in range(3))
            answer += abs(column_sum)
        print(answer)
        return

    # 状态：(A 的图案, A 的标记, B 的图案, B 的标记) -> 最大得分。
    # 一列图案是 0..7：它的 3 个二进制位分别表示三行填 O 还是 X。
    dp: dict[tuple[int, int, int, int], int] = {}
    for pattern_a in range(8):
        for pattern_b in range(8):
            dp[(pattern_a, 0, pattern_b, 0)] = 0

    # 加入新列 C，结算旧列 A，然后窗口由 (A,B) 右移成 (B,C)。
    for col_c in range(2, n):
        col_a = col_c - 2
        next_dp: dict[tuple[int, int, int, int], int] = {}

        for (pattern_a, mark_a, pattern_b, mark_b), old_score in dp.items():
            for pattern_c in range(8):
                patterns = (pattern_a, pattern_b, pattern_c)
                gain, new_mark_b, mark_c = move(
                    col_a, patterns, mark_a, mark_b, weight
                )

                new_state = (pattern_b, new_mark_b, pattern_c, mark_c)
                new_score = old_score + gain
                if new_score > next_dp.get(new_state, -10**100):
                    next_dp[new_state] = new_score

        dp = next_dp

    # 最后两列不会再滑出窗口，需要单独结算。
    answer = -10**100
    for (pattern_a, mark_a, pattern_b, mark_b), old_score in dp.items():
        total = old_score
        total += finish_column(n - 2, pattern_a, mark_a, weight)
        total += finish_column(n - 1, pattern_b, mark_b, weight)
        answer = max(answer, total)

    print(answer)


if __name__ == "__main__":
    solve()
