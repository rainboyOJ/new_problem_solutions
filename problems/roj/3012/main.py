#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-03-31 09:00
# update_at: 2026-03-31 09:00

import sys


def has_valid_fence(prefix_sums: list[float], f: int) -> bool:
    """检查是否存在长度至少为 f 且总和非负的连续子数组。

    维护扫到当前位置右端点 r 时，所有合法左端点 l (0 <= l <= r - f) 对应的
    最小前缀和 min_l。若 prefix_sums[r] - min_l >= 0，说明存在满足条件的区间。
    """
    min_l = 0.0
    for r in range(f, len(prefix_sums)):
        l = r - f
        if prefix_sums[l] < min_l:
            min_l = prefix_sums[l]
        if prefix_sums[r] >= min_l:
            return True
    return False


def check(a: list[int], f: int, mid: float) -> bool:
    """判断平均值能否达到 mid。"""
    prefix_sums = [0.0]
    total = 0.0
    for x in a:
        total += x - mid
        prefix_sums.append(total)
    return has_valid_fence(prefix_sums, f)


def max_average_fence(a: list[int], f: int) -> int:
    """二分平均值求长度至少为 f 的最大连续平均值，结果乘 1000 向下取整。"""
    left = 0.0
    right = 2000.0

    while right - left > 1e-5:
        mid = (left + right) / 2.0
        if check(a, f, mid):
            left = mid
        else:
            right = mid

    return int(right * 1000)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    try:
        first = next(data)
    except StopIteration:
        return
    n = int(first)
    f = int(next(data))
    a = [int(next(data)) for _ in range(n)]

    ans = max_average_fence(a, f)
    print(ans)


if __name__ == "__main__":
    solve()
