#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:08
# update_at: 2026-09-29 17:08

import sys

TARGETS = (1, 5, 10)  # 题面要求统计的三个整数


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    k = next(data)  # 正整数的个数
    nums = [next(data) for _ in range(k)]

    # 桶计数：cnt[v] = 值 v 出现的次数；不在 1..10 范围的值不影响三个目标值
    cnt = {v: nums.count(v) for v in TARGETS}

    print('\n'.join(map(str, (cnt[1], cnt[5], cnt[10]))))


if __name__ == "__main__":
    solve()
