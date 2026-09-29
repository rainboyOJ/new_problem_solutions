#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:19
# update_at: 2026-09-30 05:27

import sys

NO_POINT = -1  # 哨兵：表示"还没选过任何点"；所有左端点 a ≥ 0，故它一定小于任何 a


def min_points(intervals: list[tuple[int, int]]) -> int:
    """最少要点数覆盖全部闭区间：按右端点升序扫描，未覆盖的区间就取走它的右端点。"""
    last = NO_POINT  # 已选点中的最大值，即最近一次选中的点
    count = 0
    for a, b in sorted(intervals, key=lambda seg: seg[1]):  # 右端点升序：让"取 b"不会失效
        if a > last:  # 此时所有已选点都 < a，本区间必须新增点；取 b 能覆盖的后续区间最多
            last = b
            count += 1
    return count


def solve() -> None:
    nums = list(map(int, sys.stdin.buffer.read().split()))
    n = nums[0]                                                    # 区间个数
    intervals = [(nums[2 * i + 1], nums[2 * i + 2]) for i in range(n)]
    print(min_points(intervals))


if __name__ == "__main__":
    solve()
