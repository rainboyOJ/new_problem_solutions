#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:35
# update_at: 2026-09-30 08:35

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 当月发送短信的次数

    # 每条短信拆成 ceil(字数/70) 条计费，总条数 * 0.1 元
    total = sum((length + 69) // 70 for length in data)
    print(f"{total / 10:.1f}")


if __name__ == "__main__":
    solve()
