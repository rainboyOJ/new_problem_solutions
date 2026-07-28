#!/usr/bin/env python3
from typing import List


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        index_by_value: dict[int, int] = {}

        for index, value in enumerate(nums):
            complement = target - value
            if complement in index_by_value:
                return [index_by_value[complement], index]
            index_by_value[value] = index

        raise ValueError("题目保证存在唯一答案")


def main() -> None:
    """本地验证适配层；提交 LeetCode 时只保留 Solution 类即可。"""

    n, target = map(int, input().split())
    nums = list(map(int, input().split()))
    if len(nums) != n:
        raise ValueError("数组长度与 n 不一致")

    answer = Solution().twoSum(nums, target)
    print(*answer)


if __name__ == "__main__":
    main()
