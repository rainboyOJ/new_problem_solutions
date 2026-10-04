#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 10:09
# update_at: 2026-09-30 10:09

import sys


def can_place(stalls: list[int], cows: int, dist: int) -> bool:
    """间距至少 dist 时能否放下 cows 头牛（贪心：第一头放最左，之后每头都放能塞下的最左隔间）。

    每头牛都尽量往左压，给后面的牛留出最大剩余空间；若这种最省地盘的方式都放不下，
    其它摆法只会更挤，所以贪心的可行性等价于真正的可行性。
    """
    placed = 1     # 最左隔间必放一头，这是留给后面牛最多余量的摆法
    last = stalls[0]
    for pos in stalls:
        if pos - last >= dist:      # 找到下一头能放的隔间，越靠左越好
            last = pos
            placed += 1
    return placed >= cows


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, c = next(data), next(data)
    stalls = sorted(next(data) for _ in range(n))

    # 题面只保证 0 <= xi <= 1e9，没保证位置互不相同。若不同位置不足 c 个，
    # 必有一对牛同处一室，最小距离只能是 0，下面的 [1, hi] 二分区间会漏掉这个答案。
    if len(set(stalls)) < c:
        print(0)
        return

    # 答案就是"最大可行间距"，可行性关于 dist 单调（dist 越小越容易放下），故可二分。
    # 上界取把 c 头牛均摊到两端之间：间距再大，光是首尾两头就超过总跨度了。
    lo, hi = 1, (stalls[-1] - stalls[0]) // (c - 1)
    while lo < hi:
        mid = (lo + hi + 1) >> 1        # 上取整，配合 lo = mid 避免死循环
        if can_place(stalls, c, mid):
            lo = mid                    # mid 可行，答案不小于 mid
        else:
            hi = mid - 1
    print(lo)


if __name__ == "__main__":
    solve()
