#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:15
# update_at: 2026-09-29 19:15

import sys


def solve() -> None:
    n, m = map(int, sys.stdin.buffer.read().split())

    # off[j] = 1 表示灯 j 被翻过奇数次（初始全亮，翻奇数次即最终关闭）。
    # 1 号"全部关闭"、2 号"打开 2 的倍数"本质都是取反，统一按翻倍数处理。
    off = bytearray(n + 1)
    for d in range(1, m + 1):
        off[d::d] = bytes(v ^ 1 for v in off[d::d])  # 下标 d, 2d, 3d, ... 恰是 d 的倍数

    print(','.join(map(str, (j for j in range(1, n + 1) if off[j]))))


if __name__ == "__main__":
    solve()
