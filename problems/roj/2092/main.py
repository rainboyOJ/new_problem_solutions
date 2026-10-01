#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def min_cyclic_shift(s: str) -> int:
    """求长度为 n 的字符串 s 的最小表示法起始下标（0-indexed）。"""
    n = len(s)
    doubled = s + s
    i, j, k = 0, 1, 0

    while i < n and j < n and k < n:
        diff = ord(doubled[i + k]) - ord(doubled[j + k])
        if diff == 0:
            k += 1
        elif diff > 0:
            i += k + 1
            i += int(i == j)  # 保证两个候选起点不重合
            k = 0
        else:
            j += k + 1
            j += int(i == j)  # 保证两个候选起点不重合
            k = 0

    return min(i, j)


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    L = int(data[0])
    s = "".join(data[1:])
    print(min_cyclic_shift(s))


if __name__ == "__main__":
    solve()
