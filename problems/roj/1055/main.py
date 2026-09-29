#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:34
# update_at: 2026-09-29 16:34

import sys


def solve() -> None:
    year = int(sys.stdin.buffer.read())                      # 题面的 a
    # 公历闰年规则：被 4 整除是闰年；但被 100 整除时例外，需再被 400 整除。
    leap = year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)
    print('Y' if leap else 'N')


if __name__ == "__main__":
    solve()
