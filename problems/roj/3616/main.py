#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:41
# update_at: 2026-10-02 10:41

import sys

size = 0  # 矩阵边长 n，layer 系列函数都要用它换算边界


def layer(row: int, col: int) -> int:
    """(row, col) 所在的圈层号：0 表示最外圈，中心点所在层为 n//2。"""
    return min(row - 1, col - 1, size - row, size - col)


def offset_on_layer(row: int, col: int, k: int) -> int:
    """(row, col) 是第 k 层按行进顺序的第几个格子（0 起），按四条边分四段累加。"""
    side = size - 2 * k       # 第 k 层的边长
    top_len = side - 1        # 第 k 层上边的格子数（不含下个转角）
    if row - 1 == k:          # 上边：从左到右
        return col - (k + 1)
    if size - col == k:       # 右边：从上到下
        return top_len + (row - (k + 1))
    if size - row == k:       # 下边：从右到左
        return 2 * top_len + (size - k - col)
    return 3 * top_len + (size - k - row)  # 左边：从下到上


def spiral_value(row: int, col: int) -> int:
    """第 row 行第 col 列格子里的数：外圈完整层的格子总数 + 本层内的行进偏移。"""
    k = layer(row, col)
    # 前 k 层（即第 0..k-1 层）的格子总数：每层 4*边长-4，边长从 size 每层减 2
    full = sum(4 * (size - 2 * m) - 4 for m in range(k))
    return full + offset_on_layer(row, col, k) + 1


def solve() -> None:
    global size
    n, i, j = map(int, sys.stdin.buffer.read().split())
    size = n
    print(spiral_value(i, j))


if __name__ == "__main__":
    solve()
