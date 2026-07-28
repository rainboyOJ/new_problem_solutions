#!/usr/bin/env python3
from typing import List


class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        w = 0
        for i in range(len(nums)):
            if nums[i]:
                nums[w] = nums[i]
                w += 1
        for i in range(w, len(nums)):
            nums[i] = 0


def main() -> None:
    n = int(input())
    nums = list(map(int, input().split()))
    Solution().moveZeroes(nums)
    print(*nums)


if __name__ == "__main__":
    main()
