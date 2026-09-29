#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:02
# update_at: 2026-09-29 22:02

import sys
from math import factorial

MAX_N = 10000
# n! 的位数约为 n·log10(n/e)：10000! 有 35660 位，远超 Python 3.11 起默认的
# int→str 转换上限 4300 位，这里按题面上界放宽到 5·MAX_N 位。
sys.set_int_max_str_digits(5 * MAX_N)


def factorial_digits(n: int) -> str:
    """n! 的十进制字符串；n = 0 时约定 0! = 1。"""
    # Python 的 int 是任意精度，factorial 内部按位打包分治相乘，
    # 乘法的代价按机器字而不是按十进制位计，比逐位手写高精乘快得多。
    return str(factorial(n))


def solve() -> None:
    """读入一个整数 n，输出 n! 的精确值。"""
    (n,) = map(int, sys.stdin.buffer.read().split())
    print(factorial_digits(n))


if __name__ == "__main__":
    solve()
