#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:04
# update_at: 2026-10-04 14:27

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    sign = -1 if n < 0 else 1          # 负号单独保留，不参与反转
    digits = str(abs(n))[::-1].lstrip('0')  # 反转后去掉新数最高位的 0（如 380 -> 038 -> 38）
    print(sign * int(digits or '0'))    # 全是 0 时 lstrip 会得到空串，原数必为 0


if __name__ == "__main__":
    solve()
