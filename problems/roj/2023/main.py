#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys
from collections import Counter


def count_min_swaps(a: list[int]) -> int:
    """计算将只含 1, 2, 3 的序列排成升序所需的最少交换次数。"""
    c = Counter(a)
    n1, n2 = c[1], c[2]

    # 统计排完序后属于区间 i 的位置上实际出现的数字 j 的数量
    cnt1_in_2 = sum(1 for x in a[n1:n1 + n2] if x == 1)
    cnt2_in_1 = sum(1 for x in a[:n1] if x == 2)
    cnt1_in_3 = sum(1 for x in a[n1 + n2:] if x == 1)
    cnt3_in_1 = sum(1 for x in a[:n1] if x == 3)
    cnt2_in_3 = sum(1 for x in a[n1 + n2:] if x == 2)
    cnt3_in_2 = sum(1 for x in a[n1:n1 + n2] if x == 3)

    # 两两错位直接互换（1 次交换纠正 2 个数）
    direct_12 = min(cnt1_in_2, cnt2_in_1)
    direct_13 = min(cnt1_in_3, cnt3_in_1)
    direct_23 = min(cnt2_in_3, cnt3_in_2)

    # 剩下的错位必然构成 3 元环（2 次交换纠正 3 个数）
    remain = (cnt1_in_2 - direct_12) + (cnt2_in_1 - direct_12)

    return direct_12 + direct_13 + direct_23 + 2 * remain


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n = data[0]
    a = data[1:n + 1]
    print(count_min_swaps(a))


if __name__ == "__main__":
    solve()
