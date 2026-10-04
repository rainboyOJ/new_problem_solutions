#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:25
# update_at: 2026-09-29 21:25

import sys


def solve() -> None:
    """读取以 '!' 结尾的一行，输出 '!' 之前所有字符的逆序。"""
    text = sys.stdin.buffer.read().decode().rstrip('\n')
    end = text.find('!')                                # 找到终止符位置
    print(text[:end][::-1])


if __name__ == "__main__":
    solve()
