#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 02:25
# update_at: 2026-09-30 02:25

import sys


def lis_heights(nums: list[int]) -> list[int]:
    """以每个位置结尾、严格上升子序列的最大长度（LIS 经典 O(n^2) DP）。"""
    dp: list[int] = []  # dp[i] = 以 nums[i] 结尾的 LIS 长度
    for i, height in enumerate(nums):
        dp.append(1 + max((dp[j] for j in range(i) if nums[j] < height), default=0))
    return dp


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    heights = [next(data) for _ in range(n)]  # 每位同学的身高

    rise = lis_heights(heights)                # rise[i]：i 左侧（含 i）的最长严格上升
    fall = lis_heights(heights[::-1])[::-1]    # fall[i]：i 右侧（含 i）的最长严格下降

    # 峰值算两次，减 1；n<=2 时队列必然不严格，max 兜底为 0，答案输出 n
    keep = max((r + f - 1 for r, f in zip(rise, fall)), default=0)
    print(n - max(keep, 0))


if __name__ == "__main__":
    solve()
