#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:26
# update_at: 2026-09-30 02:02
#
# 数据说明：本题源仓库的测试数据由 data.py 用 randint 随机生成后未排序写出，
# 10 组输入都不是题面要求的“非降序列”，而 .out 由评测程序 std.cpp 对这些乱序
# 数组跑二分产生。因此本文件复刻 std.cpp 的迭代轨迹（含用绝对值比较距离的
# 平局规则）以保证与评测数据一致；题面语义下的标准解法（非降数组上二分插入
# 位置）见 index.md 的 ### 思路。

import sys


def nearest(a: list[int], x: int) -> int:
    """复刻评测程序 std.cpp 的语义：在 1-based 下标 [1, n] 上二分收敛到相邻两点。

    std.cpp 用 1 号下标存首元素（读入 a[1..n]），初始 left=1、right=n，循环在
    right - left == 1 时停止，所以 a[l] 与 a[r] 是相邻的两个下标。这里保留同样的
    下标区间与同样的 mid = (l + r) / 2 取整方式，使迭代轨迹与 std.cpp 逐位对应，
    便于对照；0-based 的 [0, n-1] 只是整体平移，结果与本写法完全一致。

    注意平局必须用绝对值比较：乱序数组下 a[l] 与 a[r] 可能同侧，
    移项写法会得出相反的结论。
    """
    l, r = 1, len(a) - 1                          # a[0] 是占位，有效数据在 a[1..n]
    while l < r - 1:
        mid = (l + r) >> 1
        if a[mid] > x:                            # a[mid] 偏大，收紧右界
            r = mid
        else:                                     # a[mid] <= x，收紧左界
            l = mid
    # 距离必须用绝对值比较：乱序数组下 a[l] 与 a[r] 可能同时大于或同时小于 x，
    # 此时 "a[l]-x >= x-a[r]" 这类移项写法会给出相反的结论。
    return a[l] if abs(a[l] - x) <= abs(a[r] - x) else a[r]  # 平局取 a[l]（较小下标）


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())
    n = next(data)
    a = [0] + [next(data) for _ in range(n)]      # 1-based 存储，a[0] 不用
    m = next(data)
    queries = [next(data) for _ in range(m)]
    sys.stdout.write('\n'.join(map(str, (nearest(a, x) for x in queries))) + '\n')


if __name__ == "__main__":
    solve()
