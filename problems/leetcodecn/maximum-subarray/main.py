#!/usr/bin/env python3
from typing import List


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        ans = cur = nums[0]
        for x in nums[1:]:
            cur = max(x, cur + x)
            ans = max(ans, cur)
        return ans


def main() -> None:
    n = int(input())
    nums = list(map(int, input().split()))
    print(Solution().maxSubArray(nums))


if __name__ == "__main__":
    main()
