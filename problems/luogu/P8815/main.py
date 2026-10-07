#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-05 15:21
# update_at: 2026-10-05 15:21

import sys

type Value = tuple[int, int, int]  # 一段表达式的结果：(值, & 短路次数, | 短路次数)
type Values = list[Value]          # 调度场算法的操作数栈，栈里每段是一个 Value

PRIO = {'&': 2, '|': 1}  # 运算符优先级：& 高于 |；'(' 不参与比较，取默认 0


def reduce_top(vals: Values, ops: list[str]) -> None:
    """归约一层：把栈顶运算符和左右两段结果合成一段，短路时丢弃右段的短路次数。"""
    right = vals.pop()
    left = vals.pop()
    op = ops.pop()
    lval, l_and, l_or = left
    rval, r_and, r_or = right

    if op == '&':
        if lval == 0:
            # a&b 中 a 为 0：整段值为 0，b 一整段都不求值，右段的短路次数全部作废
            vals.append((0, l_and + 1, l_or))
        else:
            vals.append((lval & rval, l_and + r_and, l_or + r_or))
    else:
        if lval == 1:
            # a|b 中 a 为 1：整段值为 1，b 一整段都不求值，右段的短路次数全部作废
            vals.append((1, l_and, l_or + 1))
        else:
            vals.append((lval | rval, l_and + r_and, l_or + r_or))


def evaluate(s: str) -> Value:
    """调度场算法边扫描边归约，直接算出整个表达式的结果。"""
    vals: Values = []
    ops: list[str] = []  # 运算符栈，只放 '&', '|', '('

    for ch in s:
        if ch in '01':
            vals.append((int(ch), 0, 0))  # 叶子：单个 0/1，自身没有短路
        elif ch == '(':
            ops.append(ch)
        elif ch == ')':
            while ops[-1] != '(':
                reduce_top(vals, ops)
            ops.pop()  # 丢掉 '('
        else:
            # 栈顶“该先算”的运算符先归约；同级从左到右，所以 >= 就弹
            while ops and ops[-1] != '(' and PRIO[ops[-1]] >= PRIO[ch]:
                reduce_top(vals, ops)
            ops.append(ch)

    while ops:
        reduce_top(vals, ops)
    return vals[0]  # 归约完栈里剩下的最后一段就是整个表达式


def solve() -> None:
    # 输入就是一整行表达式本身，没有空白可切分，直接整行读
    s = sys.stdin.readline().strip()
    value, short_and, short_or = evaluate(s)
    print(value)
    print(short_and, short_or)


if __name__ == "__main__":
    solve()
