#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:47
# update_at: 2026-09-29 15:47

import sys


def solve() -> None:
    ch = sys.stdin.buffer.read().split()[0].decode()  # 输入只有一个可见字符，空白切分顺带去掉换行
    is_odd = ord(ch) & 1 == 1                         # 码点最低位为 1，即 ASCII 值为奇数
    print("YES" if is_odd else "NO")


if __name__ == "__main__":
    solve()
