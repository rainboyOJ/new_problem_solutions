#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:55
# update_at: 2026-09-30 06:55

import sys
from operator import add, mul, sub

LEV = {'+': 1, '-': 1, '*': 2, '/': 2}  # 二元运算符优先级，调度场算法弹栈用
APPLY = {'+': add, '-': sub, '*': mul}  # 除法单独走分支：要向零取整并判除数为 0


def divide(a: int, b: int) -> int:
    """整数除法向零取整，与 C++ 的 int / int 一致（Python 的 // 是向下取整）。"""
    quotient = abs(a) // abs(b)
    return -quotient if (a < 0) != (b < 0) else quotient


def tokenize(expr: str) -> list[str] | None:
    """把中缀表达式切成记号并校验合法性；非法时返回 None。

    校验只靠“当前位置该出现哪类记号”一个状态：操作数位只接受数字、左括号和
    一元负号 '-'（直接并入后面的数字），运算符位只接受二元运算符和右括号。
    连续两个运算符、空括号、头尾运算符、括号不配对，都会落到不该出现的位置上。
    """
    tokens: list[str] = []
    expect_operand = True  # 下一个记号应当是操作数
    depth = 0              # 尚未闭合的左括号个数
    i = 0
    while i < len(expr):
        ch = expr[i]
        if ch.isdigit() or (ch == '-' and expect_operand):
            negative = ch == '-'  # 操作数位上的 '-' 是负数标志
            if negative:
                i += 1
                if i >= len(expr) or not expr[i].isdigit():
                    return None   # 一元负号后面必须紧跟数字
            j = i
            while j < len(expr) and expr[j].isdigit():
                j += 1
            tokens.append(('-' if negative else '') + expr[i:j])
            i = j
            expect_operand = False
        elif ch in '()':
            if ch == '(':
                if not expect_operand:
                    return None    # 左括号只能出现在操作数位，如 5( 这种要拒
                depth += 1
            else:
                if expect_operand or depth == 0:
                    return None    # 空括号 ()，或没有配对的右括号
                depth -= 1
            tokens.append(ch)
            expect_operand = ch == '('  # 左括号后要操作数，右括号后要运算符
            i += 1
        elif not expect_operand and ch in LEV:
            tokens.append(ch)
            expect_operand = True
            i += 1
        else:
            return None  # 运算符出现在操作数位（如 +* 连排），或非法字符
    if expect_operand or depth:
        return None  # 空表达式 / 以运算符结尾 / 左括号没闭合
    return tokens


def to_postfix(tokens: list[str]) -> list[str]:
    """调度场算法：运算符按优先级弹栈，把中缀记号改写成后缀序列。"""
    out: list[str] = []
    ops: list[str] = []
    for tok in tokens:
        if tok in LEV:
            # 栈顶优先级不低于当前运算符的先算，保证同级从左到右结合
            while ops and ops[-1] != '(' and LEV[ops[-1]] >= LEV[tok]:
                out.append(ops.pop())
            ops.append(tok)
        elif tok == '(':
            ops.append(tok)
        elif tok == ')':
            while ops[-1] != '(':
                out.append(ops.pop())
            ops.pop()  # 丢掉左括号
        else:
            out.append(tok)  # 操作数直接进输出
    while ops:
        out.append(ops.pop())
    return out


def eval_postfix(postfix: list[str]) -> int | None:
    """用操作数栈求后缀表达式的值；除数为 0 视为非法，返回 None。"""
    stack: list[int] = []
    for tok in postfix:
        if tok in LEV:
            rhs, lhs = stack.pop(), stack.pop()
            if tok == '/':
                if rhs == 0:
                    return None
                stack.append(divide(lhs, rhs))
            else:
                stack.append(APPLY[tok](lhs, rhs))
        else:
            stack.append(int(tok))
    return stack.pop()


def solve() -> None:
    # '@' 是结束符；题面样例里省略了它，取第一个 '@' 之前的部分即可兼容两种写法
    data = iter(sys.stdin.buffer.read().split(b'@'))
    expr = next(data).decode().strip()
    tokens = tokenize(expr)
    if tokens is None:
        print('NO')
        return
    value = eval_postfix(to_postfix(tokens))
    print('NO' if value is None else value)


if __name__ == "__main__":
    solve()
