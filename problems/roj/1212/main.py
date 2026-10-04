#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:40
# update_at: 2026-09-29 23:53

import sys

BASE = 65  # 'A' 的 ASCII 码，字母编号 = 字节值 - BASE，落在 0..25


def max_distinct_letters(grid: list[bytes], rows: int, cols: int) -> int:
    """从左上角出发、每步四连通、不重复经过同种字母，能走出的最长步数。

    字母表只有 26 个，所以路径长度天然被 26 卡住；用 26 位掩码记录"已经用掉
    哪些字母"，目标格能否进入只取决于它的字母是否已在掩码里。因此不需要额外的
    格子访问数组：同一字母不会在路径上出现两次，也就不可能回到走过的格子
    （回到原格必然重字母）。

    显式栈保存 (位置, 掩码, 已走长度)。进入子状态用 `mask | bit` 生成新整数再
    压栈，父状态从未被修改，兄弟分支各自读到干净快照，不需要回溯时清零。
    """
    best = 1
    # 栈元素：一维位置、该位置字母已置位的掩码、到达该位置的路径长度
    stack = [(0, 1 << (grid[0][0] - BASE), 1)]

    while stack:
        pos, mask, depth = stack.pop()
        best = max(best, depth)
        r, c = divmod(pos, cols)
        # 四个方向的邻居，越界处用 None 占位，稍后统一过滤
        neighbors = (
            (r - 1, c) if r > 0 else None,          # 上
            (r + 1, c) if r + 1 < rows else None,   # 下
            (r, c - 1) if c > 0 else None,          # 左
            (r, c + 1) if c + 1 < cols else None,   # 右
        )
        for nb in neighbors:
            if nb is None:
                continue
            nr, nc = nb
            bit = 1 << (grid[nr][nc] - BASE)
            if mask & bit:                          # 该字母已在路径上，不能进入
                continue
            stack.append((nr * cols + nc, mask | bit, depth + 1))

    return best


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    rows, cols = int(data[0]), int(data[1])
    grid = data[2:2 + rows]     # 每行是 bytes，遍历它得到的就是各字母的字节值
    print(max_distinct_letters(grid, rows, cols))


if __name__ == "__main__":
    solve()
