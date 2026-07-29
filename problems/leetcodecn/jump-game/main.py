#!/usr/bin/env python3
from typing import List


class Solution:
    def canJump(self, nums: List[int]) -> bool:
        reach = 0
        for i, x in enumerate(nums):
            if i > reach:
                return False
            reach = max(reach, i + x)
        return True


def main():
    n = int(input())
    a = list(map(int, input().split()))
    print(Solution().canJump(a))


if __name__ == "__main__":
    main()
