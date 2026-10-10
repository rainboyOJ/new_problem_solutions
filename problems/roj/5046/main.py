#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 23:30
# update_at: 2026-10-08 23:30

import sys


def solve() -> None:
    line = sys.stdin.readline()
    if not line:
        return  # 空输入：无数据可判

    # 题面说「一行字符串」，readline 保证读到空格也不截断
    s = line.rstrip('\r\n')  # 剥行尾 '\r'（CRLF 容错）与 '\n'

    # '.' 是行尾终止符，不参与回文判断；数据末尾可能没有 '.'（如样例 abccb），故需判断
    if s.endswith('.'):
        s = s[:-1]

    # 回文判断区分大小写：切片反转后直接比较
    print("Yes" if s == s[::-1] else "No")


if __name__ == "__main__":
    solve()
