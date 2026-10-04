#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 12:42
# update_at: 2026-09-29 12:42


import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    a, b, c = next(data), next(data), next(data)
    total = a + b
    # C 语义的整数除法是向零取整，Python 的 // 是向下取整：
    # 同号时两者相同；异号时先按同号算再取负，等价于向零取整
    quotient = total // c if total * c >= 0 else -(-total // c)
    print(quotient)


if __name__ == "__main__":
    solve()
