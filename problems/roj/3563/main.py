#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:04
# update_at: 2026-10-02 08:04

import sys

# 一个积木的字形：以前面左下角顶点为锚点 (0,0)，dy 向上为负、dx 向右为正。
# 三张可见面（前面、上面、右面）连边框一起整格落笔，面的内部写空格，
# 这样后画的积木能先一步抹掉被遮挡的笔画，遮挡无需单独判断。
GLYPH = (
    (-5, 2, "+---+"),  # 上面的后沿
    (-4, 1, "/   /|"),  # 上面的左右斜边与内部
    (-3, 0, "+---+ |"),  # 前面的上沿 + 右面的上半
    (-2, 0, "|   | +"),  # 前面中段 + 右面内部与后沿端点
    (-1, 0, "|   |/"),  # 前面中段 + 右面的下斜边
    (0, 0, "+---+"),  # 前面的下沿
)
CUBE = [(dy, dx + k, ch) for dy, dx, seg in GLYPH for k, ch in enumerate(seg)]  # 36 格


def paint(canvas: list[list[str]], height: list[list[int]], rows: int) -> None:
    """画家算法：按后排→前排、左→右、下→上，把每个积木的 36 格字形覆盖上画布。

    这个顺序保证右邻盖掉本格右面、前排盖掉后排、上层盖掉下层顶面；
    锚点坐标由斜投影的线性位移给出：行偏移 depth、列每格 4 列、层每层 3 行。
    """
    m, n = len(height), len(height[0])
    for i in range(m):
        depth = 2 * (m - 1 - i)  # 第 i 行相对前排往“后上”偏移：行数与列数共用
        base_y = rows - 1 - depth  # 该行最下层积木锚点所在行（前排在最后一行）
        for j in range(n):
            base_x = 4 * j + depth  # 同一锚点列
            for k in range(height[i][j]):  # k = 0 起自下而上
                y = base_y - 3 * k  # 第 k 层锚点行，每上一层抬 3 行
                for dy, dx, ch in CUBE:
                    canvas[y + dy][base_x + dx] = ch


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n = next(data), next(data)

    height: list[list[int]] = []  # height[i][j] = 第 i 行第 j 列的积木数
    for _ in range(m):
        height.append([next(data) for _ in range(n)])

    # 画布取包络：宽 = 最右锚点 + 字形 6 列 + 1；高使最高塔字形顶行恰为 0。
    width = 4 * (n - 1) + 2 * (m - 1) + 7
    rows = max(3 * height[i][j] + 2 * (m - 1 - i) for i in range(m) for j in range(n)) + 3
    canvas = [["."] * width for _ in range(rows)]

    paint(canvas, height, rows)
    sys.stdout.write("\n".join(map("".join, canvas)) + "\n")


if __name__ == "__main__":
    solve()
