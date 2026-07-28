#!/usr/bin/env python3
from typing import List


class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort()
        ans = []
        for l, r in intervals:
            if not ans or l > ans[-1][1]:
                ans.append([l, r])
            else:
                ans[-1][1] = max(ans[-1][1], r)
        return ans


def main() -> None:
    n = int(input())
    a = [list(map(int, input().split())) for _ in range(n)]
    ans = Solution().merge(a)
    for l, r in ans:
        print(l, r)


if __name__ == "__main__":
    main()
