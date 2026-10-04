#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:37
# update_at: 2026-09-29 23:37

import sys


def expand(x: int) -> str:
    """把 x 写成约定的 0/2 表示，例如 5 -> 2(2)+2(0)；x = 0 返回空串，方便递归拼接。"""
    if not x:
        return ''
    top = x.bit_length() - 1                    # 最高二进制位，即 x 中最大的那个 2 的幂的指数
    # 单个 2 的幂 2^top 的写法：指数 0 要显式写 2(0)，指数 1 按约定直接写 2，更大则递归展开指数
    head = '2(0)' if top == 0 else '2' if top == 1 else f'2({expand(top)})'
    tail = expand(x - (1 << top))               # 去掉最高位后剩下的数，例如 137 - 128 = 9
    return head + f'+{tail}' * bool(tail)


def solve() -> None:
    n = int(sys.stdin.buffer.read())
    print(expand(n))


if __name__ == "__main__":
    solve()
