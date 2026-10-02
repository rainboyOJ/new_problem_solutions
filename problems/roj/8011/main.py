#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 16:59
# update_at: 2026-10-02 16:59

import sys

DAY_MIN = 1440  # 一天的分钟数


def to_minute(day: int, hour: int, minute: int) -> int:
    """把 11 月的 (日, 时, 分) 换算成自 11 月 1 日 00:00 起的绝对分钟数。"""
    return (day - 1) * DAY_MIN + hour * 60 + minute


def solve() -> None:
    day, hour, minute = map(int, sys.stdin.read().split())
    # 起点固定：11 月 11 日 11:11；同一时间轴上相减即为经过的分钟数
    spent = to_minute(day, hour, minute) - to_minute(11, 11, 11)
    print(spent if spent >= 0 else -1)  # 结束早于开始（跨不到起点）时输出 -1


if __name__ == "__main__":
    solve()
