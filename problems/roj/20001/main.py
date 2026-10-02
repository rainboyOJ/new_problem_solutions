#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:17
# update_at: 2026-10-02 19:17

import sys


def solve() -> None:
    """读入数字串，倒序输出并保证结果不以 0 开头。"""
    digits = sys.stdin.buffer.read().split()[0].decode()  # 一行数字，长度可达 250+

    # 倒序后原串尾部的 0 变成前导 0，lstrip('0') 一次删干净；
    # 整串全 0 时会删成空串，用 or '0' 兜底（如 "0" -> "0"）。
    reversed_number = digits[::-1].lstrip('0') or '0'
    print(reversed_number)


if __name__ == "__main__":
    solve()
