#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:35
# update_at: 2026-09-30 08:35

import re
import sys
from operator import add, sub, mul, floordiv, mod

# 运算符 → 整数域实现：除法用 floordiv，保证 32+64 等价 C++ 的 /
OPS = {'+': add, '-': sub, '*': mul, '/': floordiv, '%': mod}


def solve() -> None:
    # 运算符前后可能有空格（如 `32 + 64`），空白分词会把运算符粘进运算数，
    # 所以按行读入、保留行内空格，再整行交给正则切分。
    data = iter(sys.stdin.buffer.read().splitlines())
    line = next(data).decode()  # 只丢行末换行
    a, op, b = re.split(r'\s*([+\-*/%])\s*', line.strip())  # 捕获组留住运算符
    print(OPS[op](int(a), int(b)))


if __name__ == "__main__":
    solve()
