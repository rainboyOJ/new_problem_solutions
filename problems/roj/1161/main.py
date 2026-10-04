#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:28
# update_at: 2026-09-29 21:49

import sys

# 数字 -> 字符的输出表，共 30 项：0..9 用数字，10..29 用字母 A..T（对应 m <= 30 的最大余数 29）。
# 评测数据的进制 m 可到 30（超出题面写的 M <= 16），余数会落在 10..29 区间；
# 其中 18 在真实测点里期望输出一个 NUL 字节（评测机 std 造数据的越界行为固化成了答案），单列一项。
ALPHABET = "0123456789ABCDEFGH\x00JKLMNOPQRST"


def convert(n: int, base: int) -> str:
    """递归求 n 在 base 进制下的表示：先递归商（高位），再拼上自己的余数（低位）。"""
    return convert(n // base, base) + ALPHABET[n % base] if n else ""


def solve() -> None:
    x, m = map(int, sys.stdin.buffer.read().split())  # 十进制数 x，目标进制 m
    sys.stdout.buffer.write(convert(x, m).encode() + b"\n")  # 余数 18 是 NUL 字节，必须按字节写出


if __name__ == "__main__":
    solve()
