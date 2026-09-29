#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:23
# update_at: 2026-09-30 01:23

import sys


def find_pair(nums: list[int], target: int) -> tuple[int, int] | None:
    """双指针求和为 target 的数对：首个命中即"较小的数更小"的最优解。"""
    i, j = 0, len(nums) - 1
    while i < j:
        total = nums[i] + nums[j]
        if total < target:
            i += 1  # 左端已最小，j 及其左侧都配不出 target，放弃 nums[i]
        elif total > target:
            j -= 1  # 同理放弃 nums[j]
        else:
            return nums[i], nums[j]
    return None


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    nums = sorted(next(data) for _ in range(n))  # 排序后双指针才能单调移动
    target = next(data)

    pair = find_pair(nums, target)
    print("No" if pair is None else f"{pair[0]} {pair[1]}")


if __name__ == "__main__":
    solve()
