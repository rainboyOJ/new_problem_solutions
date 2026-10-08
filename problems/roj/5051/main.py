#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 00:03
# update_at: 2026-10-09 00:14

import sys

DROPPED = b" \r"  # 要删掉的字节：空格；以及 CRLF 数据被 C++ getline 留下的行尾 '\r'
FOLD = bytes.maketrans(bytes(range(65, 91)), bytes(range(97, 123)))  # ASCII 'A'-'Z' -> 'a'-'z'


def normalize(line: bytes) -> bytes:
    """删去空格与行尾 '\r'，并把 ASCII 大写字母折叠成小写，供两行比较。"""
    return line.translate(FOLD, DROPPED)


def solve() -> None:
    """整行读入两行原文，比较规范化后的字节串是否相同。"""
    raw = sys.stdin.buffer.read()
    # 只按 '\n' 断行：str.splitlines() 还会在单独的 '\r'、'\v'、'\f'、'\x85' 等处断行，
    # 而 C++ getline 只认 '\n'，用 splitlines 会与 C++ 侧读到不同的行。
    line_a, _, rest = raw.partition(b"\n")
    line_b, _, _ = rest.partition(b"\n")  # 文件不足两行时 line_b 为空串，与 C++ 的空行等价
    equal = normalize(line_a) == normalize(line_b)
    print("YES" if equal else "NO")


if __name__ == "__main__":
    solve()
