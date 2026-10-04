#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:17
# update_at: 2026-10-04 11:22

import sys


def max_unique_subarray(seq: list[int]) -> int:
    """计算序列中最长无重复连续子区间的长度。

    使用双指针滑动窗口：
    维护当前窗口 [left, right]，用哈希表 last_pos 记录每个元素最后一次出现的下标。
    当元素再次出现时，左指针必须跳到其上次出现位置的下一个位置（注意不能回退）。
    """
    last_pos: dict[int, int] = {}
    left = 0
    ans = 0

    for right, val in enumerate(seq):
        if val in last_pos and last_pos[val] >= left:
            left = last_pos[val] + 1
        last_pos[val] = right
        ans = max(ans, right - left + 1)

    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    snows = [next(data) for _ in range(n)]
    print(max_unique_subarray(snows))


if __name__ == "__main__":
    solve()
