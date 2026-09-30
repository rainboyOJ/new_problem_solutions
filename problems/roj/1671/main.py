#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 01:35
# update_at: 2026-10-01 01:35

import sys
from itertools import accumulate

# 五级宇宙速度的门槛（米/秒），严格递增
THRESHOLDS = (7960, 11200, 16700, 115000, 2000000)

# 达到第 i 级速度后要显示的标记串：前缀累积，如第 3 级显示 "123"
MARKS = tuple(accumulate(str(level) for level in range(1, len(THRESHOLDS) + 1)))


def reached_mark(v: int) -> str:
    """返回速度 v 对应的标记串：一个都没达到返回 "0"，否则是已达标级别的前缀。"""
    reached = sum(1 for limit in THRESHOLDS if v >= limit)  # 达到的级别数
    return MARKS[reached - 1] if reached else "0"


def solve() -> None:
    v = int(sys.stdin.buffer.read().split()[0])
    print(v, reached_mark(v))


if __name__ == "__main__":
    solve()
