#!/usr/bin/env python3
from typing import List


class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        slow = fast = nums[0]
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                break
        slow = nums[0]
        while slow != fast:
            slow = nums[slow]
            fast = nums[fast]
        return slow


def main():
    n = int(input())
    a = list(map(int, input().split()))
    print(Solution().findDuplicate(a))


if __name__ == "__main__":
    main()
