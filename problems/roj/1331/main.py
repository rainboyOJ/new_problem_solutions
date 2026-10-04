#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:43
# update_at: 2026-09-30 05:49

import sys

END = '@'       # 表达式结束标志，它之后的内容（换行、多余空白）一律不看
OPERATORS = '+-*/'  # 全部运算符；够用来判定「这个非数字字符该不该触发一次归约」


def evaluate(expr: str) -> int:
    """扫描后缀表达式字符串求值：数字入栈；遇运算符弹出右、左操作数，算完把结果压回。

    只有运算数之间保证有空格，运算符可以连续出现（如 `+*-`），所以只能按字符扫描，
    不能先 split() 再分 token。多位数靠 `number * 10 + 位值` 逐位拼装。
    """
    stack: list[int] = []
    number = 0       # 正在拼装的运算数
    reading = False  # 是否正处于一个运算数内部：用于区分「数字 0」和「还没开始读数」
    for ch in expr:
        if '0' <= ch <= '9':  # 只认 ASCII 数字位，等价于题面「只含有 0-9 组成的运算数」
            number = number * 10 + int(ch)
            reading = True
        elif reading:  # 遇到任何非数字字符都表示当前运算数结束，先把它入栈
            stack.append(number)
            number, reading = 0, False
        if ch not in OPERATORS:  # 空格、换行、制表符等其余字符只当分隔符
            continue
        right = stack.pop()  # 后缀表达式中右操作数入栈更晚，所以先弹出
        left = stack.pop()
        stack.append(
            left + right if ch == '+'
            else left - right if ch == '-'
            else left * right if ch == '*'
            else left // right  # 题面保证除法整除，整除时 // 与向零截断结果一致
        )
    if reading:  # `@` 紧跟运算数时可以省掉末尾空格，这里补一次收尾
        stack.append(number)
    return stack[-1]  # 合法表达式求值完栈里恰好剩一个数，它就是答案


def solve() -> None:
    source = sys.stdin.buffer.read().decode()
    print(evaluate(source[: source.index(END)]))  # 只取 @ 之前的表达式部分


if __name__ == "__main__":
    solve()
