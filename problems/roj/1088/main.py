#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:17
# update_at: 2026-09-29 18:17

import sys


def digits_from_low(n: int) -> list[int]:
    """拆出 n 的十进制各位，低位在前；用 divmod 一次同时拿到当前位和新商。"""
    out: list[int] = []
    while n:
        n, low = divmod(n, 10)  # low 是当前个位，n 是去掉个位后的商
        out.append(low)
    return out


def solve() -> None:
    """读入一个整数，按从低位到高位的顺序输出它的每一位数字。"""
    n = int(sys.stdin.buffer.read())  # 输入只有一个整数，整体转换即可，不必切分
    print(*digits_from_low(n))        # print 的默认分隔符正好是题面要求的单个空格


if __name__ == "__main__":
    solve()
