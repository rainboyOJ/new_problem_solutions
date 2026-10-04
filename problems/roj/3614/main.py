#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:41
# update_at: 2026-10-02 10:41

import sys


def count_two_sum_numbers(nums: list[int]) -> int:
    """统计集合中能表示为另两个不同数之和的数的个数。"""
    numbers = set(nums)
    # 枚举所有“两个不同数”的组合求和；多个组合凑出同一个和只算一个目标值
    sums = {a + b for i, a in enumerate(nums) for b in nums[i + 1:]}
    return len(numbers & sums)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    nums = [next(data) for _ in range(n)]
    print(count_two_sum_numbers(nums))


if __name__ == "__main__":
    solve()
