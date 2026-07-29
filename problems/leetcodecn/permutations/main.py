#!/usr/bin/env python3
from typing import List


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        ans = []

        def dfs(dep):
            if dep == len(nums):
                ans.append(nums[:])
                return
            for i in range(dep, len(nums)):
                nums[dep], nums[i] = nums[i], nums[dep]
                dfs(dep + 1)
                nums[dep], nums[i] = nums[i], nums[dep]

        dfs(0)
        return ans


def main():
    n = int(input())
    a = list(map(int, input().split()))
    for v in Solution().permute(a):
        print(*v)


if __name__ == "__main__":
    main()
