#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:07
# update_at: 2026-10-02 11:07

import sys
from itertools import count


def total_coins(days_total: int) -> int:
    """按“连续 N 天、每天 N 枚”分段累加，返回前 days_total 天的金币总数。"""
    total = 0          # 已确认的金币累计
    left = days_total  # 还没被分段覆盖的天数
    for wage in count(1):          # 第 N 段：每天 wage 枚，共 wage 天
        days = min(wage, left)     # 最后一段可能被 days_total 截断
        total += days * wage
        left -= days
        if left == 0:              # 所有天数都被分段覆盖
            break
    return total


def solve() -> None:
    days_total = int(sys.stdin.buffer.read())
    print(total_coins(days_total))


if __name__ == "__main__":
    solve()
