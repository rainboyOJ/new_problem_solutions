#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 10:18
# update_at: 2026-10-02 10:18

import sys

MOD = 10000  # 题目要求只输出答案的最后 4 位，全程取模即可


def term_value(factors: str) -> int:
    """一个乘法项的值 mod 10000：逐个因子相乘并随手取模，避免大整数膨胀。"""
    value = 1
    for x in factors.split('*'):
        value = value * int(x) % MOD
    return value


def solve() -> None:
    expr = sys.stdin.buffer.read().decode().strip()
    # 无括号且乘法优先：整个表达式 = 若干乘法项之和，按 '+' 拆项、按 '*' 拆因子
    print(sum(term_value(group) for group in expr.split('+')) % MOD)


if __name__ == "__main__":
    solve()
