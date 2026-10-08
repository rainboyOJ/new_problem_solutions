#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 01:39
# update_at: 2026-10-09 01:42

import sys


def solve() -> None:
    """读入人数 x，输出「人数 总票价」（总票价 = 10 * x，人数在前，单空格分隔）。"""
    data = sys.stdin.buffer.read().split()
    if not data:  # 空输入直接退出，避免索引越界
        return
    x = int(data[0])
    print(f'{x} {x * 10}')  # 顺序承重：人数在前、总价在后；本题只有这两个字段


if __name__ == '__main__':
    solve()
