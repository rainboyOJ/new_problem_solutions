#!/usr/bin/env python3
class Solution:
    def climbStairs(self, n: int) -> int:
        a = b = 1
        for _ in range(2, n + 1):
            a, b = b, a + b
        return b


def main():
    print(Solution().climbStairs(int(input())))


if __name__ == "__main__":
    main()
