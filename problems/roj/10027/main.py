#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 18:56
# update_at: 2026-10-02 19:07

import sys


def solve() -> None:
    text, table, *_ = sys.stdin.read().split("\n")  # 第一行待编码串，第二行 A~Z 编码表

    # str.maketrans 把 A~Z 逐位绑定到表中字母；空格不在表里，原样保留。
    # translate 在 C 层逐字符查表，O(n) 一次扫完，等价于逐字符 if 的朴素循环。
    print(text.translate(str.maketrans("ABCDEFGHIJKLMNOPQRSTUVWXYZ", table)))


if __name__ == "__main__":
    solve()
