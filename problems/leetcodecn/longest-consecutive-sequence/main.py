#!/usr/bin/env python3
from typing import List


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        s = set(nums)
        ans = 0
        for x in s:
            if x - 1 in s:
                continue
            length = 1
            while x + length in s:
                length += 1
            ans = max(ans, length)
        return ans


def main() -> None:
    n = int(input())
    nums = list(map(int, input().split()))
    print(Solution().longestConsecutive(nums))


if __name__ == "__main__":
    main()
