#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:32
# update_at: 2026-09-29 17:32

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 测量次数（每小时一次）

    longest = run = 0  # 最长连续正常小时数 / 当前连续正常小时数
    for _ in range(n):
        systolic, diastolic = next(data), next(data)  # 收缩压、舒张压

        # 正常：收缩压 90-140 且舒张压 60-90（都含端点）
        is_normal = 90 <= systolic <= 140 and 60 <= diastolic <= 90
        run = run + 1 if is_normal else 0  # 一旦异常，当前段清零重数
        longest = max(longest, run)

    print(longest)


if __name__ == "__main__":
    solve()
