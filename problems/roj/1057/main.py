#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:35
# update_at: 2026-09-29 16:44

import operator
import sys

INVALID = "Invalid operator!"  # 操作符不在四则运算内
DIV_ZERO = "Divided by zero!"   # 除数为 0


def trunc_div(a: int, b: int) -> int:
    """C++ 风格的整除：向零取整（Python 的 // 向下取整，异号时需要修正）。"""
    q = abs(a) // abs(b)
    return q if (a < 0) == (b < 0) else -q


# 操作符分发表：键是题面的操作符字符，值是它的二元运算实现。
# "操作符是否合法"即"字符是否在表里"，校验与求值共用同一份数据。
OPS = {
    b'+': operator.add,
    b'-': operator.sub,
    b'*': operator.mul,
    b'/': trunc_div,
}


def evaluate(a: int, b: int, op: bytes) -> str:
    """算出这一行该输出的内容：非法操作符优先，其次是除零，否则查表求值。"""
    if op not in OPS:
        return INVALID
    if op == b'/' and b == 0:  # 除零只在合法除法下才算，5 0 + 仍是普通加法
        return DIV_ZERO
    return str(OPS[op](a, b))


def solve() -> None:
    x, y, op = sys.stdin.buffer.read().split()  # 两个操作数 + 一个操作符
    print(evaluate(int(x), int(y), op))


if __name__ == "__main__":
    solve()
