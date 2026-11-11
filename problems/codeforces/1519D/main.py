#!/usr/bin/env python3
import sys


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return

    n = int(tokens[0])
    a = list(map(int, tokens[1 : n + 1]))
    b = list(map(int, tokens[n + 1 : 2 * n + 1]))

    # 计算不翻转时的基准总和
    init_sum = sum(x * y for x, y in zip(a, b))
    max_sum = init_sum

    # 1. 枚举奇数长对称中心（以单点 i 为中心）
    for i in range(n):
        cur = init_sum
        l, r = i - 1, i + 1
        while l >= 0 and r < n:
            cur += (a[l] * b[r] + a[r] * b[l]) - (a[l] * b[l] + a[r] * b[r])
            if cur > max_sum:
                max_sum = cur
            l -= 1
            r += 1

    # 2. 枚举偶数长对称中心（以相邻元素 (i, i+1) 为中心）
    for i in range(n - 1):
        cur = init_sum
        l, r = i, i + 1
        while l >= 0 and r < n:
            cur += (a[l] * b[r] + a[r] * b[l]) - (a[l] * b[l] + a[r] * b[r])
            if cur > max_sum:
                max_sum = cur
            l -= 1
            r += 1

    sys.stdout.write(f"{max_sum}\n")


if __name__ == "__main__":
    solve()
