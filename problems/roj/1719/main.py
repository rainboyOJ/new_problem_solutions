#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:50
# update_at: 2026-10-07 18:50

import sys
from bisect import bisect_left
from heapq import heappop, heappush
from math import isqrt

INF = 10 ** 18   # 最短路无穷大：远大于任何可行花费（<= 250 * 10^6）

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Pile = tuple[int, int]             # 木桩坐标 (X, Y)
type Disk = tuple[int, int]             # 圆盘种类 (R, C)，半径与价格


def ceil_sqrt(s: int) -> int:
    """返回最小的 r 使 r*r >= s，即圆心距的整数向上取整。"""
    r = isqrt(s)
    return r if r * r >= s else r + 1


def pareto_front(disks: list[Disk]) -> tuple[list[int], list[int]]:
    """把圆盘种类压成 Pareto 前沿，返回（半径表, 价格表），两者都升序。

    "半径更大且价格不更高"的种类可以完全替代另一种（够得更远还更便宜），
    故只保留不被支配的：按半径从大到小扫，价格必须比所有更大半径的种类都低才留下。
    """
    cheapest = {}                       # 半径 -> 该半径下的最低价格
    for radius, cost in disks:
        if cost < cheapest.get(radius, INF):
            cheapest[radius] = cost
    radii: list[int] = []
    costs: list[int] = []
    floor = INF                         # 已保留种类（半径都比当前这个大）中的最低价格
    for radius in sorted(cheapest, reverse=True):
        if cheapest[radius] < floor:    # 半径更小却更便宜，才没被支配
            radii.append(radius)
            costs.append(cheapest[radius])
            floor = cheapest[radius]
    radii.reverse()                     # 翻成半径升序，价格随之升序
    costs.reverse()
    return radii, costs


def cheapest_bridge(piles: list[Pile], disks: list[Disk], river_w: int) -> int | None:
    """返回从 y=0 走到 y=W 的最小花费，无解返回 None。

    节点 = (木桩, 圆盘种类)，节点权 = 圆盘价格：所有触底盘是源点、任意触顶盘是终点，
    于是答案就是从地面到河对岸的点权最短路。
    """
    bl = bisect_left                    # 内层循环要跑 10^7 次，绑定成局部名省一次全局查找
    radii, costs = pareto_front(disks)
    n, p = len(piles), len(radii)
    # 圆心距向上取整：d <= r1 + r2 等价于 ceil(d) <= r1 + r2，全程整数比较
    gap = [[ceil_sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2) for x2, y2 in piles] for x1, y1 in piles]

    frontier = [p] * n                  # 木桩 k 上 [frontier[k], p) 已定最短路，前面还待松弛
    dist = [[INF] * p for _ in range(n)]
    heap: list[tuple[int, int, int]] = []
    live = list(range(n))               # frontier > 0 的木桩：只有它们还有待松弛的圆盘

    def relax(k: int, idx: int, base: int) -> None:
        """用花费 base 松弛木桩 k 上尚未定最短路的圆盘 [idx, frontier[k])。

        出堆的 base 单调不减、松弛结果 base + 价格对 base 单调，
        所以每个 (木桩, 圆盘) 状态第一次被覆盖时拿到的就是它的最终最短路。
        """
        for t in range(idx, frontier[k]):
            dist[k][t] = base + costs[t]
            heappush(heap, (dist[k][t], k, t))
        frontier[k] = idx
        if idx == 0:
            live.remove(k)              # 整根木桩都定完了，退出活跃表

    for k, (_, y) in enumerate(piles):
        relax(k, bl(radii, y), 0)       # 源点：半径 >= Y_k 的圆盘触底，代价 0 起

    while heap:
        cost, i, a = heappop(heap)
        if cost != dist[i][a]:
            continue
        if radii[a] >= river_w - piles[i][1]:
            return cost                  # 该盘触顶，出堆顺序保证这就是最小花费
        row, shift = gap[i], -radii[a]   # 跳到木桩 k 需要半径 >= 圆心距 - R_a
        for k in live[:]:                # 快照遍历：relax 会把定完的木桩移出 live
            idx = bl(radii, row[k] + shift)
            if idx < frontier[k]:
                relax(k, idx, cost)
    return None


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    test_count = next(data)

    for _ in range(test_count):
        n, m = next(data), next(data)
        river_w = next(data)
        piles: list[Pile] = [(next(data), next(data)) for _ in range(n)]
        disks: list[Disk] = [(next(data), next(data)) for _ in range(m)]
        best = cheapest_bridge(piles, disks, river_w)
        out.append('impossible' if best is None else str(best))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
