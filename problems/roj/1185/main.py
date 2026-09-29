#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:38
# update_at: 2026-09-29 22:40

import sys


def solve() -> None:
    words = sys.stdin.buffer.read().split()  # 按任意空白切分，天然吃掉 1 个或多个空格
    # 输入只含字母，字节序与 ASCII 字典序一致（大写在前），所以直接用 set 去重、sorted 排序；
    # 重复单词只留一份，最后一行也要有换行符，所以末尾补一个 b'\n'
    sys.stdout.buffer.write(b'\n'.join(sorted(set(words))) + b'\n')


if __name__ == "__main__":
    solve()
