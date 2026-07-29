#!/usr/bin/env python3
from typing import List


class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        ans = 0
        for x in nums:
            ans ^= x
        return ans


def main():
    n = int(input())
    a = list(map(int, input().split()))
    print(Solution().singleNumber(a))


if __name__ == "__main__":
    main()
