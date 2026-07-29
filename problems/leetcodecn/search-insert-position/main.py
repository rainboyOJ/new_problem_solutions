#!/usr/bin/env python3
from typing import List


class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        lo, hi = 0, len(nums)
        while lo < hi:
            m = (lo + hi) // 2
            if nums[m] >= target:
                hi = m
            else:
                lo = m + 1
        return lo


def main():
    n, t = map(int, input().split())
    a = list(map(int, input().split()))
    print(Solution().searchInsert(a, t))


if __name__ == "__main__":
    main()
