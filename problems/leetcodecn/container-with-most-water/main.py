#!/usr/bin/env python3
from typing import List


class Solution:
    def maxArea(self, height: List[int]) -> int:
        l, r, ans = 0, len(height) - 1, 0
        while l < r:
            h = min(height[l], height[r])
            ans = max(ans, (r - l) * h)
            if height[l] < height[r]:
                l += 1
            else:
                r -= 1
        return ans


def main() -> None:
    n = int(input())
    height = list(map(int, input().split()))
    print(Solution().maxArea(height))


if __name__ == "__main__":
    main()
