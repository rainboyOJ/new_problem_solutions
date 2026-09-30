#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

# 区间三元组类型：(起始位置 b, 结束位置 e, 至少种树数 t)
Interval = tuple[int, int, int]


def min_trees(intervals: list[Interval], max_pos: int) -> int:
    """计算满足所有区间要求所需的最少树木总数。

    按区间右端点从小到大贪心排序：为了尽量复用给后续区间，
    每个区间缺少的树木优先从右向左紧挨着右端点放置。
    """
    # 状态数组：planted[pos] 为 True 表示位置 pos 已种树（1-indexed）
    planted = bytearray(max_pos + 1)
    total_trees = 0

    # 优先按结束位置 e 升序排序
    for b, e, t in sorted(intervals, key=lambda iv: iv[1]):
        # 统计当前区间 [b, e] 内已经种了多少棵树
        current_count = sum(planted[p] for p in range(b, e + 1))
        need = t - current_count
        if need <= 0:
            continue

        # 从右端点向左贪心补齐缺少的树
        for p in range(e, b - 1, -1):
            if not planted[p]:
                planted[p] = 1
                total_trees += 1
                need -= 1
                if need == 0:
                    break

    return total_trees


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:
        return
    h = next(data)  # 居民需求条数（区间数）
    intervals: list[Interval] = [(next(data), next(data), next(data)) for _ in range(h)]

    ans = min_trees(intervals, n)
    print(ans)


if __name__ == "__main__":
    solve()
