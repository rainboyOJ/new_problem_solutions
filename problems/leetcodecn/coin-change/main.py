#!/usr/bin/env python3
from typing import List


class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        dp = [amount + 1] * (amount + 1)
        dp[0] = 0
        for i in range(1, amount + 1):
            for c in coins:
                if i >= c:
                    dp[i] = min(dp[i], dp[i - c] + 1)
        return -1 if dp[amount] > amount else dp[amount]


def main():
    n, amt = map(int, input().split())
    a = list(map(int, input().split()))
    print(Solution().coinChange(a, amt))


if __name__ == "__main__":
    main()
