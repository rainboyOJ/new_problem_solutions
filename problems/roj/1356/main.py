#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:52
# update_at: 2026-09-30 06:52

import sys
from collections.abc import Iterator

DIGITS = '0123456789'
BRACKETS = '()'  # 括号只影响算子的进出栈时机，本身不参与数值计算
PRECEDENCE = {'+': 1, '-': 1, '*': 2, '/': 2, '^': 3}  # 数值越大结合得越紧


def trunc_div(left: int, right: int) -> int:
    """整数除法向零截断：题面的 "/" 是普通整除，负商不向下取整。"""
    quotient = abs(left) // abs(right)
    return -quotient if (left < 0) != (right < 0) else quotient


BINARY = {
    '+': lambda x, y: x + y,  # 加法
    '-': lambda x, y: x - y,  # 减法
    '*': lambda x, y: x * y,  # 乘法
    '/': trunc_div,  # 整除
    '^': lambda x, y: x ** y,  # 幂
}


def tokens(expr: str) -> Iterator[int | str]:
    """把算式切成整数与单字符算子：整数是极长数字段，其余无关字符（换行、空格）直接丢弃。"""
    number = 0
    has_digit = False
    for char in expr:
        if char in DIGITS:
            number = number * 10 + int(char)
            has_digit = True
            continue
        if has_digit:
            yield number  # 数字段到此结束，先结算它再处理当前算符
        number, has_digit = 0, False
        if char in PRECEDENCE or char in BRACKETS:
            yield char
    if has_digit:
        yield number


def to_postfix(items: Iterator[int | str]) -> list[int | str]:
    """调度场算法：中缀转后缀（逆波兰式），把"谁先算"一次性编码进序列顺序。"""
    output: list[int | str] = []
    ops: list[str] = []
    for item in items:
        if isinstance(item, int):
            output.append(item)
        elif item == '(':
            ops.append(item)
        elif item == ')':
            while ops[-1] != '(':  # 括号内的部分已经完整，全部归约出去
                output.append(ops.pop())
            ops.pop()  # 栈顶此时必是配对的 '('，它本身不进后缀串
        else:
            while ops and ops[-1] != '(' and PRECEDENCE[ops[-1]] >= PRECEDENCE[item]:
                output.append(ops.pop())  # 先算左面更高或同级的算子，同级按从左到右
            ops.append(item)
    output += reversed(ops)  # 栈底到栈顶依次落到后缀串末尾
    return output


def evaluate(postfix: list[int | str]) -> int:
    """后缀求值：数字入栈，算子弹出右侧两个数，用 BINARY 合并后压回。"""
    stack: list[int] = []
    for item in postfix:
        if isinstance(item, int):
            stack.append(item)
        else:
            right, left = stack.pop(), stack.pop()
            stack.append(BINARY[item](left, right))
    return stack[0]


def solve() -> None:
    expr = sys.stdin.buffer.read().decode(errors='ignore')  # 数据是 CRLF，换行由 tokens 丢弃
    print(evaluate(to_postfix(tokens(expr))))


if __name__ == "__main__":
    solve()
