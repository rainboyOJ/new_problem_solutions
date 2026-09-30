#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:02
# update_at: 2026-10-01 04:02

import re
import sys
from itertools import product


def value(expr: str) -> int:
    """把空格当“拼接”求表达式的值：带空格的项整项转 int，如 '-2 3' = -23。"""
    return sum(int(term.replace(' ', '')) for term in re.findall(r'[+-]?[^+-]+', expr))


def zero_sum(n: int) -> list[str]:
    """枚举每对数字间的符号并返回所有和为 0 的表达式（按 ASCII 序）。"""
    digits = ''.join(map(str, range(1, n + 1)))
    # 符号串 ' +-' 已按 ASCII 排好，product 产出的顺序天然就是题目要求的输出顺序
    candidates = (
        ''.join(a + b for a, b in zip(digits, syms)) + digits[-1]
        for syms in product(' +-', repeat=n - 1)
    )
    return [expr for expr in candidates if value(expr) == 0]


def solve() -> None:
    n = int(sys.stdin.read())
    print('\n'.join(zero_sum(n)))


if __name__ == "__main__":
    solve()
