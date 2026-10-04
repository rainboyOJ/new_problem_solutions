#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 09:45
# update_at: 2026-09-30 09:45

import heapq
import sys


def final_value(nums: list[int], pick_smallest: bool) -> int:
    """按题目规则合并到只剩一个数，返回黑板上剩下的那个值。

    pick_smallest 为 True 表示每次取两个最小的数合并（得到最大结果）；
    否则每次取两个最大的数合并（得到最小结果）。实现上把数取负放进
    同一个小根堆，pop 出来的就是原数里最大的两个。
    """
    h = list(nums) if pick_smallest else [-x for x in nums]
    heapq.heapify(h)
    while len(h) > 1:
        x, y = heapq.heappop(h), heapq.heappop(h)
        # 合并规则 a*b+1；取负方向时重新取负放回，保持堆序含义一致
        heapq.heappush(h, x * y + 1 if pick_smallest else -(x * y + 1))
    return h[0] if pick_smallest else -h[0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    nums = [next(data) for _ in range(n)]
    print(final_value(nums, True) - final_value(nums, False))


if __name__ == "__main__":
    solve()
