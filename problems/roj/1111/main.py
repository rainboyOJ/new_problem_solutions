#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:26
# update_at: 2026-09-29 19:29

import sys

OVERLOAD_HOURS = 8  # 一天上课超过这个小时数就会不高兴


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))

    # 输入一周七天、每天两个数：zip 同一个迭代器就是"每次取一对"
    totals = [school + extra for school, extra in zip(data, data)]

    day = 0                       # 0 表示这一周都不会不高兴
    longest = OVERLOAD_HOURS      # 只在这条线以上才算"不高兴"
    for d, total in enumerate(totals, 1):
        if total > longest:       # 严格大于：时长并列时不更新，保留时间更靠前的一天
            longest, day = total, d

    print(day)


if __name__ == "__main__":
    solve()
