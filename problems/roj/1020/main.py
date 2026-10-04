#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:42
# update_at: 2026-09-29 13:42

import sys


def solve() -> None:
    tokens = iter(sys.stdin.buffer.read().split())  # 输入只有空白分隔的 token，顺序消费即可
    ch = next(tokens).decode()  # 第一个 token 就是那个可见字符的字节串
    print(ord(ch))  # ord() 返回字符在 ASCII 表中的编号


if __name__ == "__main__":
    solve()
