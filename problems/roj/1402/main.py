#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:51
# update_at: 2026-09-30 08:51

import sys

LOWER = ord('a')  # 小写字母折算 0..25 的基准
UPPER = ord('A')  # 大写字母基准：解出的明文大小写跟随密文字符


def plain_char(c: str, k: str) -> str:
    """解密一个字符：明文序号 = (密文序号 - 密钥位偏移) mod 26，大小写跟随密文。"""
    shift = ord(k.lower()) - LOWER  # 密钥位折算成 0..25 的加密偏移
    base = LOWER if c.islower() else UPPER
    return chr((ord(c) - base - shift) % 26 + base)


def solve() -> None:
    key, cipher = sys.stdin.read().split()  # 密钥与密文都只含字母，按空白切开即可
    klen = len(key)
    print(''.join(plain_char(c, key[i % klen]) for i, c in enumerate(cipher)))


if __name__ == "__main__":
    solve()
