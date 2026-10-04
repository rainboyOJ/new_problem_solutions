#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 23:35
# update_at: 2026-10-01 23:35

import sys

ORIGIN = 100_001      # 坐标整体平移量：原坐标 [-100000, 100000] 变成 [1, 200001]
SIZE = 1 << 18        # 线段树的叶子数，取 2 的幂且大于 200001
GROUND = 0            # 地面编号；它的两个端点都取原点，落在上面等于已经走出场地

STAMP: list[int] = [0] * (SIZE * 2)     # 节点整段被覆盖的层号；层号越大表示覆盖越晚
WHO: list[int] = [0] * (SIZE * 2)       # 节点整段被哪条围栏覆盖，0 表示地面


def assign(left: int, right: int, value: int) -> None:
    """把横坐标区间 [left, right] 整段覆盖成围栏 value。

    只写在能拼出这个区间的 O(log SIZE) 个节点上，不往叶子推；覆盖时间直接用层号
    value（层号随处理顺序递增），点查询时沿根到叶取时间戳最大的节点就是最后一次覆盖。
    """
    left += SIZE
    right += SIZE + 1
    while left < right:
        if left & 1:
            STAMP[left], WHO[left] = value, value
            left += 1
        if right & 1:
            right -= 1
            STAMP[right], WHO[right] = value, value
        left >>= 1
        right >>= 1


def query(x: int) -> int:
    """横坐标 x 正上方最近的一条围栏编号（它上方没有围栏时是地面 GROUND）。"""
    node = x + SIZE
    latest, who = 0, GROUND
    while node:
        if STAMP[node] > latest:        # 越晚的覆盖越贴近上方，会遮住更早的覆盖
            latest, who = STAMP[node], WHO[node]
        node >>= 1
    return who


def ground_cost(fences: list[tuple[int, int]], down: list[tuple[int, int]], x: int) -> int:
    """从 (x, 某个高度) 竖直下落，再沿着接住它的那条围栏走到端点下到地面。

    自由下落途中不做水平移动，所以接住奶牛的那条围栏是唯一的；站上去以后，
    最优走法只取决于站在哪个端点，于是取"走左端点"和"走右端点"的较小值。
    """
    below = query(x)
    (left, right), (dl, dr) = fences[below], down[below]
    return min(abs(left - x) + dl, abs(right - x) + dr)


def endpoint_costs(fences: list[tuple[int, int]]) -> list[tuple[int, int]]:
    """自底向上算出每条围栏左右端点到地面所需的最少水平距离。

    第 0 项是当作地面用的虚拟围栏，两个端点都在原点，所以距离是 (0, 0)。
    每层先查两端点脚下的围栏（此时树里只有更低的层），再把本层覆盖上去——
    顺序颠倒会让端点查到自己。
    """
    down: list[tuple[int, int]] = [(0, 0)] * len(fences)
    for level in range(1, len(fences)):
        left, right = fences[level]
        down[level] = (ground_cost(fences, down, left), ground_cost(fences, down, right))
        assign(left, right, level)
    return down


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, s = next(data), next(data) + ORIGIN

    # 围栏编号就是层号 y；GROUND 代表地面，它的端点取原点，落到它上面等于已经出场地
    fences: list[tuple[int, int]] = [(ORIGIN, ORIGIN)] + [
        (next(data) + ORIGIN, next(data) + ORIGIN) for _ in range(n)
    ]

    print(ground_cost(fences, endpoint_costs(fences), s))


if __name__ == "__main__":
    solve()
