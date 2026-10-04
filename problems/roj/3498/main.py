#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 03:11
# update_at: 2026-10-02 03:11

import re
import sys

TERM = re.compile(r'[+-]?(?:\d+[a-z]?|[a-z])')  # 一项：可选符号 + 数字（可带字母）或单个字母


def balance(side: str, direction: int) -> tuple[int, int]:
    """把半边的每一项移到方程左边：返回（未知数系数和，常数和），direction 表示这半边的正负号。"""
    coef = const = 0
    for term in TERM.findall(side):
        sign = -1 if term[0] == '-' else 1  # 项首的 + / - 就是这一项的符号
        body = term.lstrip('+-')
        if body[-1].isalpha():              # 未知数项：`a`、`-a` 省略了系数 1
            coef += sign * direction * int(body[:-1] or '1')
        else:                               # 常数项
            const += sign * direction * int(body)
    return coef, const


def solve() -> None:
    data = iter(sys.stdin.read().split())  # 整行方程不含空格，按空白切开只有一个 token
    equation = next(data)
    left, right = equation.split('=')
    coef, const = balance(left, 1)
    rcoef, rconst = balance(right, -1)  # 右半边整体移项到左边
    coef, const = coef + rcoef, const + rconst
    answer = -const / coef
    if answer == 0:
        answer = 0.0                    # 抵消 -0.0，避免输出 -0.000
    name = re.search(r'[a-z]', equation).group()  # 方程里唯一的小写字母就是未知数
    print(f'{name}={answer:.3f}')


if __name__ == '__main__':
    solve()
