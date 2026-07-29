#!/usr/bin/env python3
from typing import List


class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        heights.append(0)
        st = []
        ans = 0
        for i, h in enumerate(heights):
            while st and heights[st[-1]] > h:
                hh = heights[st.pop()]
                l = st[-1] if st else -1
                ans = max(ans, hh * (i - l - 1))
            st.append(i)
        heights.pop()
        return ans


def main():
    n = int(input())
    a = list(map(int, input().split()))
    print(Solution().largestRectangleArea(a))


if __name__ == "__main__":
    main()
