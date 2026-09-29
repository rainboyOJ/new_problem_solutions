#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:11
# update_at: 2026-09-29 13:11

import sys


def solve() -> None:
    """读入 x a y b，输出可持续养活的人口数（亿）：资源年增长量 (y*b - x*a)/(b-a)。"""
    x, a, y, b = map(int, sys.stdin.buffer.read().split())

    # 两份资源账本相减消去初始资源，分子 p 为“总消耗差”，分母 q 为“年数差”
    p, q = y * b - x * a, b - a

    # 标准程序用整型量相除，等价于 C++ 的整数除法（向零截断）；Python 的 // 是向下取整，
    # 数据中存在 -4.44 → -4 这类负值，必须显式改成向零截断
    quotient = abs(p) // abs(q) * (-1 if (p < 0) != (q < 0) else 1)
    print(f"{quotient}.00")


if __name__ == "__main__":
    solve()
