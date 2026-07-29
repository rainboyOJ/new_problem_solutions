#!/usr/bin/env python3
from typing import List


class Solution:
    def jump(self, nums: List[int]) -> int:
        n = len(nums)
        jumps = curEnd = farthest = 0
        for i in range(n - 1):
            farthest = max(farthest, i + nums[i])
            if i == curEnd:
                jumps += 1
                curEnd = farthest
        return jumps


def main():
    n = int(input())
    a = list(map(int, input().split()))
    print(Solution().jump(a))


if __name__ == "__main__":
    main()
