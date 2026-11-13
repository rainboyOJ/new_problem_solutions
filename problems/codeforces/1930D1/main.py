#!/usr/bin/env python3
import sys


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)

    t = int(next(it))
    out = []

    for _ in range(t):
        n = int(next(it))
        s = next(it)

        dp = [0] * (n + 5)
        total_ans = 0

        for i in range(n - 1, -1, -1):
            if s[i] == "0":
                dp[i] = dp[i + 1]
            else:
                dp[i] = dp[i + 3] + (n - i)
            total_ans += dp[i]

        out.append(str(total_ans))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
