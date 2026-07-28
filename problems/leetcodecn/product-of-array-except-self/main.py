#!/usr/bin/env python3
from typing import List


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [1] * n
        left = 1
        for i in range(n):
            ans[i] = left
            left *= nums[i]
        right = 1
        for i in range(n - 1, -1, -1):
            ans[i] *= right
            right *= nums[i]
        return ans


def main() -> None:
    n = int(input())
    nums = list(map(int, input().split()))
    print(*Solution().productExceptSelf(nums))


if __name__ == "__main__":
    main()
