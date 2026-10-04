#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:42
# update_at: 2026-10-01 02:42

import sys
from collections.abc import Iterator
from itertools import count, islice

BASE_MAX = 10  # 题面进制范围：二进制到十进制
NEED = 2       # “两种以上进制”即至少 2 种进制下回文


def is_palindrome(value: int, base: int) -> bool:
    """value 在 base 进制下的数码序列是否左右对称。

    除到商为 0 为止，得到的余数顺序就是低位到高位；首位数码一定非零，
    所以比较数码序列与它的逆序即可，不必再额外判前导零。
    """
    digits: list[int] = []
    while value:
        digits.append(value % base)
        value //= base
    return digits == digits[::-1]


def palindrome_bases(value: int) -> int:
    """value 在 2~10 进制中成为回文数的进制个数。"""
    return sum(is_palindrome(value, base) for base in range(2, BASE_MAX + 1))


def dual_palindromes(n: int, s: int) -> Iterator[int]:
    """按从小到大顺序产出前 n 个“大于 s 的双重回文数”。"""
    return islice((v for v in count(s + 1) if palindrome_bases(v) >= NEED), n)  # 找到 n 个即停


def solve() -> None:
    n, s = map(int, sys.stdin.buffer.read().split())
    print(*dual_palindromes(n, s), sep="\n")


if __name__ == "__main__":
    solve()
