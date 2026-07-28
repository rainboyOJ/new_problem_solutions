#!/usr/bin/env python3
from typing import List


class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        n = len(nums)
        k %= n
        nums.reverse()
        nums[:k] = reversed(nums[:k])
        nums[k:] = reversed(nums[k:])


def main() -> None:
    n, k = map(int, input().split())
    nums = list(map(int, input().split()))
    Solution().rotate(nums, k)
    print(*nums)


if __name__ == "__main__":
    main()
