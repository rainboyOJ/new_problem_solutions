#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:15
# update_at: 2026-09-29 21:20

from math import isqrt


def is_prime(n: int) -> bool:
    """试除法判素数：2 到 ⌊√n⌋ 之间没有任何因子，n 就是素数。"""
    return n > 1 and all(n % d != 0 for d in range(2, isqrt(n) + 1))


# 三位回文数形如 aba，即 100a + 10b + a = 101a + 10b；a 取 1..9、b 取 0..9，共 90 个
THREE_DIGIT_PALINDROMES = tuple(101 * a + 10 * b for a in range(1, 10) for b in range(10))


def solve() -> None:
    """本题没有输入：直接生成候选回文数，筛出素数后一个数一行输出。"""
    print("\n".join(map(str, filter(is_prime, THREE_DIGIT_PALINDROMES))))


if __name__ == "__main__":
    solve()
