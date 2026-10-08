#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 01:43
# update_at: 2026-10-09 01:43

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a = next(data, None)
    b = next(data, None)
    if a is None or b is None:
        return  # 防御非法输入：题面保证恰好读入两个正整数

    a, b = b, a  # 元组解包完成交换，等价于临时变量三次赋值，无算术运算
    print(a, b)  # print 默认以单个空格分隔，并补一个行末换行


if __name__ == "__main__":
    solve()
