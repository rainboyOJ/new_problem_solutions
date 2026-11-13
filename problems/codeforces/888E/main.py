#!/usr/bin/env python3
import bisect
import sys


def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)

    n = int(next(it))
    m = int(next(it))
    a = [int(next(it)) % m for _ in range(n)]

    mid = n // 2
    left = a[:mid]
    right = a[mid:]

    # 生成前半部分子集和余数
    sum_a = [0]
    for x in left:
        sum_a += [(s + x) % m for s in sum_a]

    # 生成后半部分子集和余数
    sum_b = [0]
    for x in right:
        sum_b += [(s + x) % m for s in sum_b]

    sum_b = sorted(set(sum_b))
    max_b = sum_b[-1]

    ans = 0
    for u in sum_a:
        # 情况 1: u + v < m => v < m - u
        idx = bisect.bisect_left(sum_b, m - u)
        if idx > 0:
            val = u + sum_b[idx - 1]
            if val > ans:
                ans = val
        # 情况 2: u + v >= m => v 越大越好
        val2 = (u + max_b) % m
        if val2 > ans:
            ans = val2

    print(ans)


if __name__ == "__main__":
    solve()
