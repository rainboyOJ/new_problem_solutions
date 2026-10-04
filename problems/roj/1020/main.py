#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:42
# update_at: 2026-09-29 13:42

import sys


def solve() -> None:
    ch = sys.stdin.buffer.read().split()[0].decode()  # 输入只有一个可见字符，空白切分即可取到
    print(ord(ch))  # ord() 返回字符在 ASCII 表中的编号


if __name__ == "__main__":
    solve()
