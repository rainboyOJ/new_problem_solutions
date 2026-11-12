#!/usr/bin/env python3
import sys


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    it = iter(lines)

    t = int(next(it))
    MOD = 1_000_000_007
    out = []

    for _ in range(t):
        n = int(next(it))
        k = int(next(it))
        a = [int(next(it)) for _ in range(n)]

        # dp[mask] 存储按位与结果等于 mask 的非空子序列方案数
        dp = [0] * 64

        for x in a:
            new_dp = list(dp)  # 双缓冲拷贝不选 x 的历史方案
            new_dp[x] = (new_dp[x] + 1) % MOD  # x 单独成段

            for mask in range(64):
                if dp[mask]:
                    nxt = mask & x
                    new_dp[nxt] = (new_dp[nxt] + dp[mask]) % MOD

            dp = new_dp

        # 统计二进制 1 的个数恰好为 k 的方案数之和
        ans = sum(dp[mask] for mask in range(64) if mask.bit_count() == k) % MOD
        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
