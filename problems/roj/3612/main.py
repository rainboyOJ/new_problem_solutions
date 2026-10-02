#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:29
# update_at: 2026-10-02 10:29

import sys


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    h = list(map(int, data[1 : n + 1]))

    # up / down：当前最长"抖动"序列的长度，
    # up = 末段在上升，down = 末段在下降；初始各留一株花，长度都是 1
    up = down = 1
    for i in range(1, n):
        if h[i] > h[i - 1]:      # 新花更高：只能接在"下降"序列后形成上升段
            up = down + 1        # down 保守不变：这时接上不会让 down 更优
        elif h[i] < h[i - 1]:    # 新花更矮：只能接在"上升"序列后形成下降段
            down = up + 1
        # 相等的花必被移走，两个状态都维持不变

    print(max(up, down))


if __name__ == "__main__":
    solve()
