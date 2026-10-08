#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 01:11
# update_at: 2026-10-09 01:11

import sys

# 输出必须与 C++ 的 %g 同语义：6 位有效数字、去掉尾随零、大数转科学计数法。
# 实测数据点：626077 726791 + -> 1.35287e+06，999999 999999 * -> 9.99998e+11，
# 1000000 1000000 * -> 1e+12。Python 默认 print(float) 会输出 1352870.0 / 1e+12 之类，
# 与 C++ 完全不同，所以这里只能走 '%g'。


def solve() -> None:
    """读入「数 数 运算符」，按运算符分派输出；除零与非法运算符各走错误分支。"""
    token = sys.stdin.buffer.read().split()
    if len(token) < 3:  # 题面保证每行三项；不足时静默退出，与 C++ 侧行为一致
        return
    a = float(token[0])
    b = float(token[1])
    op = token[2].decode()

    if op == '+':
        result = a + b
    elif op == '-':
        result = a - b
    elif op == '*':
        result = a * b
    elif op == '/':
        # 除数为 0 是题面规定的错误分支，先判零再相除，避免 ZeroDivisionError
        if b == 0.0:
            print('Divided by zero!')
            return
        result = a / b
    else:
        print('Invalid operator!')
        return

    print('%g' % result)  # 与 C++ printf("%g") 逐字节一致（见上方注释）


if __name__ == '__main__':
    solve()
