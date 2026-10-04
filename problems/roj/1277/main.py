#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:03
# update_at: 2026-09-30 03:06

import sys


def read_grid(n: int, data: list[int]) -> list[list[int]]:
    """把三元组列表铺成 (n+2)×(n+2) 的网格，下标从 1 开始，界外补 0。

    以 `0 0 0` 结束；收尾行可能只给出一两个 0，用 zip 按位置切三元组即可自动丢弃余数。
    """
    grid = [[0] * (n + 2) for _ in range(n + 2)]
    triples = zip(*[iter(data)] * 3)  # 每 3 个相邻元素一组，余数自动丢弃
    for row, col, value in triples:
        if not (row or col or value):  # 0 0 0 是结束标记
            break
        grid[row][col] = value        # 重复给出的格子以后出现的数为准
    return grid


def best_two_paths(grid: list[list[int]], n: int) -> int:
    """两条 (1,1)→(n,n) 只向右/向下的路径能取得的最大数字和（同格只算一次）。

    两条路都走 s-1 步时，各自终点必在第 s 条反对角线 i+j=s 上，所以按步数同步推进：
    f[i][j] = 两条路分别停在 (i, s-i) 与 (j, s-j) 时的最大收益，s 为当前反对角线。
    这样状态从 O(n^4) 降到每层 O(n^2)、总和 O(n^3)，且天然保证两条路同步。
    """
    neg = -1  # 不可达状态用负数标记：本题所有数值非负，"有限"与"不可达"因此可区分
    f = [[neg] * (n + 1) for _ in range(n + 1)]
    f[1][1] = grid[1][1]  # 两条路都从 A 出发，起点数字只计一次

    for s in range(3, 2 * n + 1):  # 反对角线 i+j=2 上两条路都在 (1,1)，不必转移
        nf = [[neg] * (n + 1) for _ in range(n + 1)]
        rows = range(max(1, s - n), min(n, s - 1) + 1)  # 该反对角线上合法的行号
        for i, j in ((i, j) for i in rows for j in rows):
            # 两条路各自"上一步"只能从左边或上边来，共 4 种组合
            best = max(f[i - 1][j - 1], f[i - 1][j], f[i][j - 1], f[i][j])
            if best >= 0:
                gain = grid[i][s - i] + (0 if i == j else grid[j][s - j])  # 同格只取一次
                nf[i][j] = max(nf[i][j], best + gain)
        f = nf

    return f[n][n]


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    print(best_two_paths(read_grid(n, data[1:]), n))


if __name__ == "__main__":
    solve()
