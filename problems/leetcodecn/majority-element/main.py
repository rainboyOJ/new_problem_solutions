#!/usr/bin/env python3
from typing import List


class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        cand = cnt = 0
        for x in nums:
            if cnt == 0:
                cand = x
            cnt += 1 if x == cand else -1
        return cand


def main():
    n = int(input())
    a = list(map(int, input().split()))
    print(Solution().majorityElement(a))


if __name__ == "__main__":
    main()
