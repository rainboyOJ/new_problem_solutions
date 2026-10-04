#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:53
# update_at: 2026-10-02 09:53

import sys


def undo(ch: str, kch: str) -> str:
    """® 运算的逆：明文字母 = 密文字母 − 密钥字母（mod 26），忽略大小写、大小写取自密文。"""
    plain = (ord(ch.lower()) - ord(kch.lower())) % 26  # 明文在字母表中的序号 A=0
    return chr(plain + ord('A' if ch.isupper() else 'a'))


def solve() -> None:
    lines = [ln.strip() for ln in sys.stdin.read().splitlines() if ln.strip()]
    key = lines[0]    # 密钥，长度 ≤ 100，只有字母
    cipher = lines[1]  # 密文，长度 ≤ 1000；密钥不足时循环重复使用
    # 逐位用密钥对应字母解密一个字母，密钥下标 i % len(key) 即"重复使用"的落点
    print(''.join(undo(ch, key[i % len(key)]) for i, ch in enumerate(cipher)))


if __name__ == "__main__":
    solve()
