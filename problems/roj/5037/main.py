#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:46
# update_at: 2026-10-08 22:46

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, 0)
    if n <= 0:
        return  # 题面保证 n >= 1，这里只防御非法输入

    a = [next(data) for _ in range(n)]
    shifted = a[1:] + a[:1]  # 左旋一位：首元素接到末尾，其余元素依次前移一格
    print(' '.join(map(str, shifted)))


if __name__ == "__main__":
    solve()
