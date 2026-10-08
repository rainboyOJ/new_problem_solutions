#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:46
# update_at: 2026-10-08 22:46

import sys


def solve() -> None:
    """读入全部整数并按输入逆序输出；个数不定，靠读到的 token 数决定（n ≤ 100）。"""
    # 逆序输出要整体倒着走，先把全部 token 物化成 list（不能只顺序消费一次）。
    nums = list(map(int, sys.stdin.buffer.read().split()))
    if nums:  # 空输入时不输出任何内容（题面保证 n ≥ 1）
        print(' '.join(map(str, nums[::-1])))


if __name__ == "__main__":
    solve()
