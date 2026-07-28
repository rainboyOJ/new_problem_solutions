#!/usr/bin/env python3
from typing import List
from collections import defaultdict


class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        cnt = defaultdict(int)
        cnt[0] = 1
        s = ans = 0
        for x in nums:
            s += x
            ans += cnt[s - k]
            cnt[s] += 1
        return ans


def main() -> None:
    n, k = map(int, input().split())
    nums = list(map(int, input().split()))
    print(Solution().subarraySum(nums, k))


if __name__ == "__main__":
    main()
