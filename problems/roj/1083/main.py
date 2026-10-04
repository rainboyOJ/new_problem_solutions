#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 17:55
# update_at: 2026-09-29 17:55

import sys

WEEK = [  # 星期名，下标 = (a^b mod 7) - 1：0 → Monday … 6 → Sunday
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday",
]


def solve() -> None:
    a, b = map(int, sys.stdin.buffer.read().split())

    r = pow(a, b, 7)  # 三参数 pow 即模意义快速幂，大指数也不需要展开
    print(WEEK[r - 1])  # r=0 表示整除 7，余 7 天一循环，仍是 Sunday


if __name__ == "__main__":
    solve()
