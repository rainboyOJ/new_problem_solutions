#!/usr/bin/env python3
from typing import List


class Solution:
    def trap(self, height: List[int]) -> int:
        l, r, lmax, rmax, ans = 0, len(height) - 1, 0, 0, 0
        while l < r:
            if height[l] < height[r]:
                if height[l] >= lmax:
                    lmax = height[l]
                else:
                    ans += lmax - height[l]
                l += 1
            else:
                if height[r] >= rmax:
                    rmax = height[r]
                else:
                    ans += rmax - height[r]
                r -= 1
        return ans


def main() -> None:
    n = int(input())
    height = list(map(int, input().split()))
    print(Solution().trap(height))


if __name__ == "__main__":
    main()
