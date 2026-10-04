#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:20
# update_at: 2026-10-02 11:20

import sys


def solve() -> None:
    n = int(sys.stdin.readline())
    square = [[0] * n for _ in range(n)]
    row, col = 0, n // 2  # 数字 1 的落点：第一行正中间

    for value in range(1, n * n + 1):
        square[row][col] = value
        # 四条规则按题面顺序判定：分支互斥，书写顺序即优先级。
        # 后两个分支隐含 row > 0 且 col < n-1，所以下标始终在棋盘内。
        if row == 0 and col != n - 1:
            row, col = n - 1, col + 1         # 上边非右上角 → 最后一行、右一列
        elif col == n - 1 and row != 0:
            row, col = row - 1, 0             # 右边非右上角 → 第一列、上一行
        elif row == 0 and col == n - 1:
            row += 1                          # 右上角 → 正下方
        elif square[row - 1][col + 1] == 0:   # 右上方为空 → 填右上方
            row, col = row - 1, col + 1
        else:                                 # 右上方已被占 → 填正下方
            row += 1

    print('\n'.join(' '.join(map(str, line)) for line in square))


if __name__ == "__main__":
    solve()
