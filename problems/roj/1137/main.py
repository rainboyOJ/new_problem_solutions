#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-06 10:00
# update_at: 2026-07-06 10:00

import sys

import string

SHIFT = 3  # 加密时字母表循环左移的位数，解密时右移回来

# 解密用的字母表右移 3 翻译表：'a'->'d'、'z'->'c'，大小写各一套
_LOWER = string.ascii_lowercase
SHIFTED = _LOWER[SHIFT:] + _LOWER[:SHIFT]
TABLE = str.maketrans(string.ascii_letters, SHIFTED + SHIFTED.upper())


def solve() -> None:
    cipher = sys.stdin.read().strip()  # 密文，长度 < 50，只含大小写字母

    # 加密顺序：左移 3 → 逆序 → 大小写反转；解密按逆序撤销
    swapped = cipher.swapcase()   # 撤销第 3 步：大小写反转（自逆）
    reversed_ = swapped[::-1]     # 撤销第 2 步：逆序（自逆）
    print(reversed_.translate(TABLE))  # 撤销第 1 步：循环右移 3


if __name__ == "__main__":
    solve()
