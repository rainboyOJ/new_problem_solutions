#!/usr/bin/env python3
from typing import List


class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(n):
            while 1 <= nums[i] <= n and nums[nums[i] - 1] != nums[i]:
                x = nums[i] - 1
                nums[i], nums[x] = nums[x], nums[i]
        for i in range(n):
            if nums[i] != i + 1:
                return i + 1
        return n + 1


def main() -> None:
    n = int(input())
    nums = list(map(int, input().split()))
    print(Solution().firstMissingPositive(nums))


if __name__ == "__main__":
    main()
