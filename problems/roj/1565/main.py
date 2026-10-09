#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 08:34
# update_at: 2026-10-09 08:34

import sys
from bisect import bisect_left, insort


def solve() -> None:
    """逐天累加最小波动值：第 i 天取已出现营业额的有序序列中 a[i] 的前驱与后继，
    f_i = min(|a[i]-前驱|, |a[i]-后继|)；第 1 天按题面规定直接取 a[1]。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))

    n = next(data, None)
    if n is None:
        return

    values = [next(data, None) for _ in range(n)]  # 数据缺行时补 None 作保护
    first = values[0] if values else None
    if first is None:
        return

    total = first          # 第一天的最小波动值 = 第一天的营业额
    appeared: list[int] = [first]  # 已经出现过的营业额，始终保持升序

    for value in values[1:]:
        if value is None:
            break

        pos = bisect_left(appeared, value)  # 第一个 >= value 的位置，即后继
        best = appeared[pos] - value if pos < len(appeared) else None
        if pos > 0:
            diff = value - appeared[pos - 1]  # 前驱：小于 value 的最大元素
            best = diff if best is None else min(best, diff)

        total += best
        insort(appeared, value)  # 保持升序；list 插入为 O(n)，整体 O(n^2)，但常数小可过

    print(total)


if __name__ == "__main__":
    solve()
