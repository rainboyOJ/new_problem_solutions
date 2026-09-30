#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 11:53
# update_at: 2026-09-30 11:53

import sys


def max_repeats(s: bytes) -> int:
    """返回 s 最多由多少个相同子串重复连接而成。"""
    # s 在 s+s 中首次再现的位置（从 1 起）= 能整除 len(s) 的最小周期，
    # CPython 的 find 用 Two-Way 算法，最坏也是线性时间。
    period = (s + s).find(s, 1)
    return len(s) // period


def solve() -> None:
    # 每行一个仅含字母的串，读到 "." 结束；按空白切分即可逐串处理
    for s in sys.stdin.buffer.read().split():
        if s == b".":
            break
        print(max_repeats(s))


if __name__ == "__main__":
    solve()
