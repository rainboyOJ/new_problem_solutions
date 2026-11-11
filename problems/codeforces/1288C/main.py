#!/usr/bin/env python3
import math
import sys

MOD = 10**9 + 7


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    n, m = int(tokens[0]), int(tokens[1])

    # 原问题等价于在 [1, n] 中有放回选择 2m 个非降整数
    # 即经典可重组合 C(n + 2m - 1, 2m)
    ans = math.comb(n + 2 * m - 1, 2 * m) % MOD
    sys.stdout.write(f"{ans}\n")


if __name__ == "__main__":
    solve()
