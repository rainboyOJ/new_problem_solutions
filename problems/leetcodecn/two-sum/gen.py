#!/usr/bin/env python3
import random


def count_solutions(nums: list[int], target: int) -> int:
    count = 0
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] + nums[j] == target:
                count += 1
    return count


def main() -> None:
    random.seed()

    while True:
        n = random.randint(2, 12)
        nums = random.sample(range(-50, 51), n)
        left, right = random.sample(range(n), 2)
        target = nums[left] + nums[right]
        if count_solutions(nums, target) == 1:
            break

    print(n, target)
    print(*nums)


if __name__ == "__main__":
    main()
