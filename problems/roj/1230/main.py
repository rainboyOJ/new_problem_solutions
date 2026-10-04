#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:42
# update_at: 2026-09-30 00:42

import sys


def maximal_points(points: list[tuple[int, int]]) -> list[tuple[int, int]]:
    """按 x 从小到大返回所有极大点（没有任何其它点同时不小于它的 x 与 y）。

    按 x 降序、y 降序扫描：已扫过的点 x 都不小于当前点，其中最大的 y 记为 max_y。
    当前点被支配 <=> 存在已扫过的点 y' >= y <=> y <= max_y，故 y > max_y 即为极大点。
    """
    found: list[tuple[int, int]] = []
    max_y = -1  # 坐标非负，-1 是比任何真实 y 都小的哨兵
    for x, y in sorted(points, reverse=True):  # 元组排序：x 降序，x 相同则 y 降序
        if y > max_y:
            found.append((x, y))
            max_y = y
    return found[::-1]  # 扫描得到 x 递减，反转即为题目要求的 x 递增


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    points = [(next(data), next(data)) for _ in range(n)]

    print(','.join(f'({x},{y})' for x, y in maximal_points(points)))


if __name__ == "__main__":
    solve()
