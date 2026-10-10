#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 23:31
# update_at: 2026-10-08 23:41

import sys

BLANKS = b" \t\n\r\v\f"  # cin >> 会跳过的空白字符集合，用来对齐两侧的取字符语义


def solve() -> None:
    """整行读入原文，取第 2 行头两个非空白字符 A、B，把原文中的 A 全换成 B 后输出。"""
    raw = sys.stdin.buffer.read()
    if not raw:  # 完全没有输入，与 C++ 侧一致地不输出任何内容
        return
    # 只按 '\n' 断行：str.splitlines() 还会在单独的 '\r' 处断行，会把一行原文拆成两行
    first_line, _, rest = raw.partition(b"\n")
    text = first_line.rstrip(b"\r")                 # 剔除 CRLF 数据在行尾残留的 '\r'
    chars = rest.translate(None, BLANKS)            # 丢掉空白后剩下的前两个字节就是 A、B
    if len(chars) >= 2:
        text = text.replace(chars[0:1], chars[1:2])  # 按单字节字符替换，区分大小写
    sys.stdout.buffer.write(text + b"\n")


if __name__ == "__main__":
    solve()
