#!/usr/bin/env python3
import sys


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    n = int(lines[0])
    a = [int(x) for x in lines[1:]]

    MOD = 1_000_000_007

    # dp[k] 表示当前为止，长度为 k 的优秀子序列的总方案数
    dp = [0] * (n + 1)
    dp[0] = 1

    for x in a:
        # 1. 试除法提取当前数字 x 的全部因子 (截断至 <= n)
        divs = []
        for d in range(1, int(x**0.5) + 1):
            if x % d == 0:
                if d <= n:
                    divs.append(d)
                if d * d != x and x // d <= n:
                    divs.append(x // d)

        # 2. 降序排列，避免当前元素在同一子序列中被重复多次使用 (类比 0-1 背包)
        divs.sort(reverse=True)

        # 3. 状态转移
        for d in divs:
            dp[d] = (dp[d] + dp[d - 1]) % MOD

    print(sum(dp[1:]) % MOD)


if __name__ == "__main__":
    solve()
