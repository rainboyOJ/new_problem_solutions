#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 16:22
# update_at: 2026-10-02 16:22

import sys

DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"  # 数符表：下标即位值，>=10 用大写字母


def to_base(value: int, base: int) -> str:
    """十进制整数转 base 进制字符串：反复除 base 取余，余数倒序即高位在前。"""
    if value == 0:
        return "0"
    out: list[str] = []
    while value:
        value, r = divmod(value, base)
        out.append(DIGITS[r])
    return "".join(reversed(out))


def solve() -> None:
    data = iter(sys.stdin.read().split())
    n = int(next(data))
    out: list[str] = []
    for _ in range(n):
        s = next(data)             # a 进制的原数
        a, b = int(next(data)), int(next(data))
        # int(s, a) 直接按 a 进制解析（0-9/A-Z 均支持），再压成 b 进制
        out.append(to_base(int(s, a), b))
    print("\n".join(out))


if __name__ == "__main__":
    solve()
