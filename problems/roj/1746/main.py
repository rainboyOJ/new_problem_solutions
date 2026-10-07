#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 20:58
# update_at: 2026-10-07 21:06

import sys

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Table = list[int]        # 一维展开（行优先）的 n x m 表，下标 i*m+j
type Levels = list[Table]     # 固定行跨度 a 时，列跨度 b = 0,1,2,... 的各层表

FLUSH = 1 << 16               # 输出攒够这么多行就落盘，避免 1e6 个字符串同时驻留


def row_levels(n: int, m: int, base: Table, la: int) -> Levels:
    """行方向稀疏表：lv[a][i*m+j] = max{ base[i'][j] : i <= i' < i + 2^a }。"""
    lv = [base]
    for a in range(1, la):
        half = 1 << (a - 1)
        span = half << 1
        prev = lv[-1]
        cur = [0] * (n * m)
        # 只有 i + 2^a <= n 的行能放下一个完整的 2^a 行块，其余位置永远查不到
        for i in range(n - span + 1):
            lo = i * m
            hi = (i + half) * m
            cur[lo:lo + m] = map(max, prev[lo:lo + m], prev[hi:hi + m])
        lv.append(cur)
    return lv


def col_levels(n: int, m: int, rows: Table, lb: int) -> Levels:
    """在某一 a 层上做列方向合并：lv[b][i*m+j] = max{ rows[i*m+j'] : j <= j' < j + 2^b }。"""
    lv = [rows]
    for b in range(1, lb):
        half = 1 << (b - 1)
        span = half << 1
        prev = lv[-1]
        cur = [0] * (n * m)
        width = m - span + 1  # 列方向同理，只有前 width 列能放下完整的 2^b 列块
        for i in range(n):
            lo = i * m
            cur[lo:lo + width] = map(max, prev[lo:lo + width], prev[lo + half:lo + half + width])
        lv.append(cur)
    return lv


def build_tables(n: int, m: int, grid: Table) -> list[Levels]:
    """二维稀疏表：tab[a][b][i*m+j] 是以 (i,j) 为左上角的 2^a 行 x 2^b 列方块的最大值。"""
    la, lb = n.bit_length(), m.bit_length()  # 2^(la-1) <= n < 2^la，即楼层数 = log2(n)+1
    return [col_levels(n, m, rows, lb) for rows in row_levels(n, m, grid, la)]


def solve() -> None:
    data = sys.stdin.buffer
    n, m, K = map(int, data.readline().split())

    grid: Table = []
    while len(grid) < n * m and (line := data.readline()):  # 矩阵可能跨行，读满 n*m 个数
        grid += map(int, line.split())
    tab = build_tables(n, m, grid)

    write = sys.stdout.write
    out: list[str] = []
    for _ in range(K):
        x1, y1, x2, y2 = map(int, data.readline().split())
        height, width = x2 - x1 + 1, y2 - y1 + 1
        # 2^a x 2^b 的方块只要四个角各放一块，就能完全盖住整个询问矩形
        a, b = height.bit_length() - 1, width.bit_length() - 1
        t = tab[a][b]
        dr = height - (1 << a)  # 下方方块相对左上角方块的行偏移（0 表示高度恰是 2 的幂）
        dc = width - (1 << b)   # 右方方块相对左上角方块的列偏移
        lt = (x1 - 1) * m + y1 - 1   # 左上角方块的下标
        lbot = lt + dr * m           # 左下角方块的下标
        best = max(t[lt], t[lt + dc], t[lbot], t[lbot + dc])
        out.append(str(best))
        if len(out) == FLUSH:
            write('\n'.join(out))
            write('\n')
            out.clear()

    if out:
        write('\n'.join(out))
        write('\n')


if __name__ == "__main__":
    solve()
