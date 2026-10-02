#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:57
# update_at: 2026-10-02 12:04

import sys

MDAYS = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)  # 平年每月天数


def solve() -> None:
    date1, date2 = map(int, sys.stdin.read().split())
    first_year, last_year = date1 // 10000, date2 // 10000  # 起止年份

    ans = 0
    for year in range(first_year, last_year + 1):
        # 关键观察：8 位回文日期的后四位 = 前四位年份的倒序，年份一旦选定，月日就被唯一确定
        mmdd = str(year)[::-1]
        month, day = int(mmdd[:2]), int(mmdd[2:])
        if not 1 <= month <= 12:
            continue                      # 倒序出的月份不在 1~12，该年没有回文日期
        days = MDAYS[month - 1]
        is_leap = year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)  # 题面的闰年规则
        if month == 2 and is_leap:
            days += 1                      # 闰年 2 月 29 天
        if not 1 <= day <= days:
            continue                      # 该月没有这一天，构不成真实日期
        date = year * 10000 + month * 100 + day  # 拼回 8 位日期
        ans += date1 <= date <= date2      # 只有首尾年份可能越出区间

    print(ans)


if __name__ == "__main__":
    solve()
