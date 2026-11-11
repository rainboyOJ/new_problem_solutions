#!/usr/bin/env python3
import sys


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    n, *vals = map(int, tokens)
    a, b = vals[:n], vals[n:]

    ans = cur_base = sum(x * y for x, y in zip(a, b))

    # 统一奇数长（单点 (i-1, i+1)）与偶数长（相邻缝隙 (i, i+1)）的所有 2n-1 个对称轴起点
    centers = [(i - 1, i + 1) for i in range(n)] + [(i, i + 1) for i in range(n - 1)]

    # 利用 zip 同步向两侧辐射，净增量因式分解为 (a[i] - a[j]) * (b[j] - b[i])
    for l, r in centers:
        cur = cur_base
        for i, j in zip(range(l, -1, -1), range(r, n)):
            cur += (a[i] - a[j]) * (b[j] - b[i])
            if cur > ans:
                ans = cur

    sys.stdout.write(f"{ans}\n")


if __name__ == "__main__":
    solve()
