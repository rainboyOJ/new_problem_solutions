#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:53
# update_at: 2026-10-01 17:53

import sys
import bisect

MX: list[int] = []    # 线段树节点：该区间内所有窗口底位置的覆盖亮度最大值
LAZY: list[int] = []  # 线段树节点：还没下传给儿子的区间加标记


def range_add(node: int, lo: int, hi: int, l: int, r: int, delta: int) -> None:
    """把窗口底区间 [l, r] 上每个位置的覆盖亮度加 delta。"""
    if r < lo or hi < l:
        return
    if l <= lo and hi <= r:
        MX[node] += delta
        LAZY[node] += delta
        return
    if LAZY[node]:  # 下传标记：儿子的最大值同样被整段抬高
        for child in (node * 2, node * 2 + 1):
            MX[child] += LAZY[node]
            LAZY[child] += LAZY[node]
        LAZY[node] = 0
    mid = (lo + hi) >> 1
    range_add(node * 2, lo, mid, l, r, delta)
    range_add(node * 2 + 1, mid + 1, hi, l, r, delta)
    MX[node] = max(MX[node * 2], MX[node * 2 + 1]) + LAZY[node]


def solve() -> None:
    global MX, LAZY
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []

    while True:
        try:
            n = next(data)
        except StopIteration:
            break
        width, height = next(data), next(data)

        stars = [(next(data), next(data), next(data)) for _ in range(n)]

        # 离散化窗口底位置：覆盖亮度只在区间端点 y-height+1 和 y 处变化，
        # 每颗星对应底边区间 [y-height+1, y]（边界上的星不算，所以左端取 +1）。
        points = sorted({v for _, y, _ in stars for v in (y - height + 1, y)})
        m = len(points)

        # 每颗星拆成两个事件：x 进入窗口左边界时 +c，右边界越过它时 -c。
        events: list[tuple[int, int, int, int, int]] = []
        for x, y, c in stars:
            l = bisect.bisect_left(points, y - height + 1)
            r = bisect.bisect_left(points, y)
            events += [(x, 1, c, l, r), (x + width, -1, c, l, r)]
        # x 相同先加后减：左边界贴上某颗星时它已在窗内，右边界压住它时已移出。
        events.sort(key=lambda e: (e[0], -e[1]))

        MX = [0] * (4 * m)
        LAZY = [0] * (4 * m)
        ans = 0
        i = 0
        while i < 2 * n:
            x = events[i][0]
            while i < 2 * n and events[i][0] == x:  # 同一条竖线：整列一起扫进/扫出
                _, sign, c, l, r = events[i]
                range_add(1, 0, m - 1, l, r, sign * c)
                i += 1
            # 扫到下一条竖线前，窗口左右可停在任意位置，覆盖亮度只由窗底决定。
            ans = max(ans, MX[1])
        out += [str(ans)]

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
