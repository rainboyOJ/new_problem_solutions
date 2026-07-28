#!/usr/bin/env python3
from typing import List
from collections import deque


class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        q = deque()
        ans = []
        for i, x in enumerate(nums):
            while q and q[0] <= i - k:
                q.popleft()
            while q and nums[q[-1]] <= x:
                q.pop()
            q.append(i)
            if i >= k - 1:
                ans.append(nums[q[0]])
        return ans


def main() -> None:
    n, k = map(int, input().split())
    nums = list(map(int, input().split()))
    print(*Solution().maxSlidingWindow(nums, k))


if __name__ == "__main__":
    main()
