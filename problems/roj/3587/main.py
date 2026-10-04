#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:20
# update_at: 2026-10-02 09:32

import sys

MOD = 10007          # 方案数对 10007 取模
PREC = {'+': 1, '*': 2}   # 题面规定 × 先算、⊕ 后算，同级从左到右


def reduce_top(opds: list[tuple[int, int]], ops: list[str]) -> None:
    """弹出栈顶运算符，把它的两个操作数 (取0方案数, 取1方案数) 合并后压回。

    两个子表达式的横线互不相交，所以合并时方案数直接相乘；
    整体方案 = 两边各自全部方案之积，再按运算规则拆成 0/1 两份。
    """
    b0, b1 = opds.pop()
    a0, a1 = opds.pop()
    whole = (a0 + a1) * (b0 + b1) % MOD   # 合并后的全部填法
    if ops.pop() == '*':                   # ×(AND)：两边都是 1 才得 1
        one = a1 * b1 % MOD
        opds.append(((whole - one) % MOD, one))
    else:                                  # ⊕(OR)：两边都是 0 才得 0
        zero = a0 * b0 % MOD
        opds.append((zero, (whole - zero) % MOD))


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    length = int(next(data))  # 第 1 个 token L：运算符与括号个数，横线都夹在它们之间
    s = next(data).decode()   # 第 2 个 token：只剩 + * ( ) 的半成品表达式

    opds: list[tuple[int, int]] = []   # 操作数栈：(该子表达式为 0 的方案数, 为 1 的方案数)
    ops: list[str] = []                # 运算符栈
    expect = True                      # 当前位置该出现操作数（横线或左括号）

    for c in s:
        # 期待操作数却直接遇到运算符 → 运算符前面藏了一条横线
        if expect and c != '(':
            opds.append((1, 1))        # 单条横线取 0、取 1 各 1 种填法
            expect = False
        if c in '+*':
            # 栈顶运算符不比当前低级（× 先于 ⊕、同级从左到右）就先弹出来算
            while ops and ops[-1] != '(' and PREC[ops[-1]] >= PREC[c]:
                reduce_top(opds, ops)
            ops.append(c)
            expect = True              # 运算符后面必然跟一个操作数
        elif c == '(':
            ops.append(c)              # 左括号入栈，等里面的表达式算完再弹
        elif c == ')':
            while ops[-1] != '(':
                reduce_top(opds, ops)
            ops.pop()                  # 去掉左括号，整个括号体作为一个操作数
            expect = False

    if expect:                         # 表达式以横线收尾
        opds.append((1, 1))
    while ops:
        reduce_top(opds, ops)

    print(opds[0][0])


if __name__ == "__main__":
    solve()
