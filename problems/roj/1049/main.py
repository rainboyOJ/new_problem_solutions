#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:21
# update_at: 2026-09-29 16:21

import sys

CLASS_DAYS = frozenset({1, 3, 5})  # 有课的日子：周一、周三、周五（题目给出的三个冲突日）


def solve() -> None:
    day = int(sys.stdin.buffer.read().split()[0])  # 邀请日期，数字 1..7 表示周一到周日
    has_class = day in CLASS_DAYS  # 落在有课集合里就不能赴约，其余日子都可以
    print("NO" if has_class else "YES")


if __name__ == "__main__":
    solve()
