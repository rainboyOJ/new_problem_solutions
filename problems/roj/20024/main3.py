#!/usr/bin/env python3
"""ROJ 20024《棋》：五列窗口 DP（main2.py 的短写法）。

和 main2.py 完全同一套算法，只是把"手工预处理"换成 Python 现成的工具：

    main2.py：build_lines() + window_code()/decode_window() + COLORED[9^5] 手工建表
    main3.py：四个列表推导写出 LINES，再用 functools.cache 按需缓存染色掩码

一列用 3bit 表示（第 r 位是 1 表示 (r,c) 画 X）。三连最多跨 3 列，所以凑齐 5 列后
正中间那一列的染色情况就完全确定，可以一次性结算；每读一列就滑动这个 5 列窗口。

写法兼容 Python 3.15。代码短，但运行速度较慢。
"""

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
def colored_mask(window) -> int:
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


def middle_score(window, col: int, weight: list[list[int]]) -> int:
    """五列都已知时，计算正中间那一列（棋盘第 col 列）的完整得分。"""
    mask = colored_mask(window)
    return sum(
        (1 if get_color(window[2], r) else -1) * weight[r][col]  # X 红 +，O 蓝 -
        for r in range(3)
        if mask >> r & 1
    )


def solve() -> None:
    n = int(input())
    weight = [list(map(int, input().split())) for _ in range(3)]

    # 状态是最近至多 4 列的图案（棋盘外写 None），值是已经结算完的最大得分。
    dp = {(None, None): 0}

    # 枚举 n 列真实棋盘，再补两个 None，让最后两列也能成为窗口中心。
    for next_col in range(n + 2):
        choices = range(8) if next_col < n else (None,)
        nxt = {}

        for state, score in dp.items():
            for pattern in choices:
                window = state + (pattern,)

                # 凑齐五列后，中间列左右各有两列，它的颜色已经完全确定。
                gain = middle_score(window, next_col - 2, weight) if len(window) == 5 else 0

                new_state = window[-4:]
                nxt[new_state] = max(nxt.get(new_state, NEG), score + gain)

        dp = nxt

    print(max(dp.values()))


if __name__ == "__main__":
    solve()
