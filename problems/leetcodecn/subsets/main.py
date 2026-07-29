#!/usr/bin/env python3
from typing import List


class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        ans, cur = [], []

        def dfs(i):
            if i == len(nums):
                ans.append(cur[:])
                return
            dfs(i + 1)
            cur.append(nums[i])
            dfs(i + 1)
            cur.pop()

        dfs(0)
        return ans


def main():
    n = int(input())
    a = list(map(int, input().split()))
    for v in Solution().subsets(a):
        print(*v)


if __name__ == "__main__":
    main()
