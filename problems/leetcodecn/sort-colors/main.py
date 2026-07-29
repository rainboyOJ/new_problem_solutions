#!/usr/bin/env python3
from typing import List


class Solution:
    def sortColors(self, nums: List[int]) -> None:
        l = m = 0
        r = len(nums) - 1
        while m <= r:
            if nums[m] == 0:
                nums[l], nums[m] = nums[m], nums[l]
                l += 1
                m += 1
            elif nums[m] == 1:
                m += 1
            else:
                nums[m], nums[r] = nums[r], nums[m]
                r -= 1


def main():
    n = int(input())
    a = list(map(int, input().split()))
    Solution().sortColors(a)
    print(*a)


if __name__ == "__main__":
    main()
