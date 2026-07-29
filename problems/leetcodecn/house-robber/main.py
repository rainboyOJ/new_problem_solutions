#!/usr/bin/env python3
from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        prev_two = prev_one = 0
        for value in nums:
            current = max(prev_one, prev_two + value)
            prev_two, prev_one = prev_one, current
        return prev_one


def main():
    n = int(input())
    a = list(map(int, input().split()))
    print(Solution().rob(a))


if __name__ == "__main__":
    main()
