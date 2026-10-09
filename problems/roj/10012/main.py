#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 22:30
# update_at: 2026-10-10 00:05

import re
import sys

MATCH_MINUTES = 3 * 60 + 30   # 比赛时长 210 分钟
DAY_MINUTES = 24 * 60         # 一天的总分钟数 1440


def solve() -> None:
    """读入 hh:mm，输出加 3 小时 30 分钟后的时刻（跨日对一天 1440 分钟取模）。"""
    # 按「非数字字符」切分：题面样例用全角「：」，std.cpp 用半角 ':'，两种都要能解析。
    parts = re.split(r'\D+', sys.stdin.read().strip())
    if len(parts) < 2:
        return
    hour, minute = map(int, parts[:2])
    total = (hour * 60 + minute + MATCH_MINUTES) % DAY_MINUTES
    print(f'{total // 60:02d}:{total % 60:02d}')


if __name__ == '__main__':
    solve()
