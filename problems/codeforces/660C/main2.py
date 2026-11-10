#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-10 11:05
# update_at: 2026-11-10 11:05

import sys
from itertools import accumulate


def solve_by_binary_search(n: int, k: int, a: list[int]) -> tuple[int, list[int]]:
    """用二分答案求最多修改 k 个 0 时最长连续 1 的长度及修改后数组。"""
    # 0 的前缀和数组：pref[i] 表示 a[0..i-1] 中 0 的数量
    pref = [0] + list(accumulate(1 if x == 0 else 0 for x in a))

    def check(length: int) -> int | None:
        """检查是否存在长度为 length 且 0 的个数 <= k 的窗口；若存在返回其起始下标。"""
        for i in range(n - length + 1):
            if pref[i + length] - pref[i] <= k:
                return i
        return None

    # 二分最大可行长度 [0, n]
    low, high = 0, n
    best_len, best_l = 0, 0

    while low <= high:
        mid = (low + high) // 2
        start = check(mid)
        if start is not None:
            best_len = mid
            best_l = start
            low = mid + 1
        else:
            high = mid - 1

    for i in range(best_l, best_l + best_len):
        a[i] = 1

    return best_len, a


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    token = next(data, None)
    if token is None:
        return
    n = int(token)
    k = int(next(data))
    a = [int(next(data)) for _ in range(n)]

    best_len, res = solve_by_binary_search(n, k, a)
    print(best_len)
    print(" ".join(map(str, res)))


if __name__ == "__main__":
    solve()
