#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:22
# update_at: 2026-10-04 12:50

import sys

WALK_TIME_X6 = 5        # 步行 1.2 m/s 的耗时 s/1.2，两边同乘 6 后为 5s，全程只剩整数
BIKE_TIME_X6 = 2        # 骑车 3 m/s 的耗时 s/3，同乘 6 后为 2s
BIKE_OVERHEAD_X6 = 300  # 找车开锁 27 秒 + 停车锁车 23 秒 = 50 秒，同乘 6 后为 300

VERDICT = {True: "Bike", False: "Walk"}  # 骑车严格更省时判 Bike，骑车更慢判 Walk


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    distance = next(data)                               # 这次办事要行走的距离，单位米
    walk_x6 = WALK_TIME_X6 * distance                   # 步行总耗时放大 6 倍
    bike_x6 = BIKE_TIME_X6 * distance + BIKE_OVERHEAD_X6  # 骑车总耗时放大 6 倍
    # 同乘正数不改大小关系，可以用整数精确比较；相等即题面的 All，临界距离由 2s+300 = 5s 解出 s = 100
    bike_faster = bike_x6 < walk_x6
    same_speed = bike_x6 == walk_x6
    print("All" if same_speed else VERDICT[bike_faster])


if __name__ == "__main__":
    solve()
