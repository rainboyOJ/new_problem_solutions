#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys

# 规则平年各月天数
MONTH_DAYS = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]


def is_leap(year: int) -> bool:
    """判断年份是否为闰年。4 的倍数且非 100 的倍数，或 400 的倍数。"""
    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)


def days_of_month(year: int, month: int) -> int:
    """返回给定年月的总天数（1-indexed）。"""
    return 29 if month == 2 and is_leap(year) else MONTH_DAYS[month - 1]


def count_thirteens(n: int) -> list[int]:
    """统计从 1900 年开始的 n 年中，每月 13 号落在星期六、日、一至五的次数。"""
    # 0 代表星期六，1 代表星期日，...，6 代表星期五
    # 1900-01-01 是星期一，经过 12 天到 1900-01-13 为星期六，故初始星期为 0 (星期六)
    counts = [0] * 7
    weekday = 0
    for year in range(1900, 1900 + n):
        for month in range(1, 13):
            counts[weekday] += 1
            weekday = (weekday + days_of_month(year, month)) % 7
    return counts


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    n = int(tokens[0])
    counts = count_thirteens(n)
    print(" ".join(map(str, counts)))


if __name__ == "__main__":
    solve()
