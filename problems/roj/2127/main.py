#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:45
# update_at: 2026-10-08 07:45

import sys
from itertools import zip_longest


def add_vertically(a: str, b: str) -> str:
    """竖式加法：低位对齐逐位相加、进位往上传递，返回无前导零的十进制结果。"""
    carry = 0
    low_to_high: list[str] = []  # 结果从低位往高位收集，输出前整体翻转
    # 倒序遍历两个加数，短的那边补 '0'，等价于 C++ 里全局数组初值全为 0
    for x, y in zip_longest(reversed(a), reversed(b), fillvalue='0'):
        carry, digit = divmod(int(x) + int(y) + carry, 10)  # 本位留 digit，进位传高位
        low_to_high.append(str(digit))
    if carry:
        low_to_high.append('1')  # 最高位进位，如 99 + 1 = 100
    return ''.join(reversed(low_to_high)).lstrip('0') or '0'  # 去前导零，0 + 0 输出 0


def solve() -> None:
    data = iter(sys.stdin.read().split())
    a, b = next(data), next(data)
    print(add_vertically(a, b))


if __name__ == "__main__":
    solve()
