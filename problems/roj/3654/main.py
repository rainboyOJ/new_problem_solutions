#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:31
# update_at: 2026-10-02 13:31

import sys

SKIP = ' \n\r'  # 题面规定不计入统计的字符：空格与换行（\r 兼容 CRLF 行尾）


def solve() -> None:
    """统计标题字符串中不为空格、不为换行的字符个数。"""
    title = sys.stdin.buffer.read().decode()  # 一次读完整份输入，行内空格原样保留
    print(sum(ch not in SKIP for ch in title))


if __name__ == "__main__":
    solve()
