#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:38
# update_at: 2026-09-29 19:38

import sys


def solve() -> None:
    n, i, j = map(int, sys.stdin.read().split())

    same_row = [(i, c) for c in range(1, n + 1)]                    # 同一行：列从左到右
    same_col = [(r, j) for r in range(1, n + 1)]                    # 同一列：行从上到下

    diff = i - j  # 主对角线不变量：行号 - 列号
    # 行从左上角 max(1,1+diff) 扫到右下角 min(n,n+diff)，列随之确定
    main_diag = [(r, r - diff) for r in range(max(1, 1 + diff), min(n, n + diff) + 1)]

    total = i + j  # 副对角线不变量：行号 + 列号
    # 行从 min(n, total-1)（左下角）倒着扫到 max(1, total-n)（右上角）
    anti_diag = [(r, total - r) for r in range(min(n, total - 1), max(1, total - n) - 1, -1)]

    out = '\n'.join(
        ' '.join(f'({x},{y})' for x, y in line)
        for line in (same_row, same_col, main_diag, anti_diag)
    )
    print(out)


if __name__ == "__main__":
    solve()
