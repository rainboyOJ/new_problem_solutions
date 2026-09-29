#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:10
# update_at: 2026-09-29 22:10

import sys

ZERO = ord('0')  # 字符数字与数值的偏移量，减法比 int() 逐位转换快也更好读


def add_digits(a: str, b: str) -> str:
    """模拟竖式加法：从最低位对齐逐位相加，进位 carry 只取 0 或 1。"""
    i, j, carry = len(a) - 1, len(b) - 1, 0
    out: list[str] = []  # 从低位往高位收集，最后整体反转

    while i >= 0 or j >= 0 or carry:                 # 循环条件含 carry：最高位还要再进一次位
        s = carry + (ord(a[i]) - ZERO if i >= 0 else 0) + (ord(b[j]) - ZERO if j >= 0 else 0)
        out.append(chr(s % 10 + ZERO))               # 本位保留 s 的个位
        carry = s // 10                              # 进位交给下一轮
        i -= 1
        j -= 1

    return ''.join(reversed(out))


def solve() -> None:
    a, b = sys.stdin.buffer.read().split()           # 两个操作数最多 200 位，可能带前导 0
    # 结果按数值输出：先去掉和的前导 0，全为 0（如 0 + 0）时保留一个 0
    print(add_digits(a.decode(), b.decode()).lstrip('0') or '0')


if __name__ == "__main__":
    solve()
