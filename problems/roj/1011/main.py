#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    confirmed, died = map(int, sys.stdin.buffer.read().split())  # 确诊数、死亡数
    rate = died / confirmed * 100  # 死亡率：死亡数 ÷ 确诊数，换算成百分数
    print(f"{rate:.3f}%")


if __name__ == "__main__":
    solve()
