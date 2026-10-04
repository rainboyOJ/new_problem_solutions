#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:05
# update_at: 2026-10-01 12:05

import sys

# 运算符优先级：数字越大越先算。UNARY 是取负号（'~'），它高于 '*' '/' 而低于 '^'，
# 与数学及 C/Python 的习惯一致：-2^2 = -(2^2) = -4，而 (-2)^2 = 4。
UNARY = '~'
LEVEL = {'+': 1, '-': 1, '*': 2, '/': 2, UNARY: 3, '^': 4}


def trunc_div(a: int, b: int) -> int:
    """题面的 / 是整除：像 C++ 那样向零取整，而不是 Python 的向下取整。"""
    return a // b if a * b >= 0 else -(-a // b)


def apply(op: str, a: int, b: int) -> int:
    """按二元运算符 op 计算操作数 a、b 的结果。

    '^' 用 int(a ** b)：指数非负时是精确整数；指数为负（如 2^-2）时按 C++ 整型
    语义截断成 0，而不是 Python 的浮点 0.25。
    """
    return (a + b if op == '+' else
            a - b if op == '-' else
            a * b if op == '*' else
            trunc_div(a, b) if op == '/' else
            int(a ** b))


def drop_extra_close(expr: str) -> str:
    """丢掉左边没有 '(' 可配对的右括号；多余的左括号留到收尾时丢弃。"""
    depth, kept = 0, []
    for c in expr:
        if c == ')' and depth == 0:          # 没人能跟它配对，直接删
            continue
        depth += (c == '(') - (c == ')')
        kept.append(c)
    return ''.join(kept)


def evaluate(expr: str) -> int:
    """算符优先法求值：从左往右扫一趟，遇到已经定序的运算就立刻结算。"""
    s = drop_extra_close(expr)
    values: list[int] = []                   # 操作数栈
    ops: list[str] = []                      # 运算符栈（含 '('）
    expect_operand = True                    # 该位置应出现操作数：开头、'(' 后、运算符后
    i, n = 0, len(s)

    def reduce_top() -> None:
        """结算栈顶：取负号弹 1 个操作数，二元运算符弹 2 个，孤立的 '(' 只丢弃。"""
        op = ops.pop()
        if op == '(':
            return
        if op == UNARY:
            values[-1] = -values[-1]
            return
        b, a = values.pop(), values.pop()
        values.append(apply(op, a, b))

    while i < n:
        c = s[i]
        if c.isdigit():
            j = i
            while j < n and s[j].isdigit():  # 多位数
                j += 1
            values.append(int(s[i:j]))
            i, expect_operand = j, False
            continue
        i += 1
        if c == '(':
            ops.append(c)
            expect_operand = True
        elif c == ')':
            while ops[-1] != '(':            # 括号内部先算干净
                reduce_top()
            ops.pop()                        # 丢掉配对的 '('
            expect_operand = False
        elif expect_operand:                 # 操作数位置上的正负号：一元运算符
            if c == '-':
                ops.append(UNARY)            # 本轮不出栈：负号只能作用于紧跟其后的运算数
            # 正号不改值，直接忽略
        else:
            # 栈顶优先级 >= 当前运算符，说明它先算；取等号让同级从左到右结合。
            while ops and ops[-1] != '(' and LEVEL[ops[-1]] >= LEVEL[c]:
                reduce_top()
            ops.append(c)
            expect_operand = True

    while ops:                               # 收尾：清空运算符栈
        reduce_top()
    return values[-1]


def solve() -> None:
    expr = ''.join(sys.stdin.read().split())  # 表达式内部无空白，去掉换行等字符
    print(evaluate(expr))


if __name__ == "__main__":
    solve()
