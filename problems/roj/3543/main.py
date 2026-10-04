#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:00
# update_at: 2026-10-02 07:00

import sys

OPS = "+-*^"  # 四个可判定的二元运算符（左结合）


def calc(tokens: str, x: int) -> int:
    """求表达式在 a = x 处的值：运算符优先级 ^ > * > +/-，同级从左到右。"""
    s = tokens.replace(" ", "")  # 消掉多余空格，词法就只剩数、a、括号、运算符
    pos = 0                      # 全局扫描位置

    def parse_expr() -> int:
        """加减层：把若干乘积项按从左到右的 +/- 累加。"""
        nonlocal pos
        value = parse_term()
        while pos < len(s) and s[pos] in "+-":
            op = s[pos]
            pos += 1
            rhs = parse_term()
            value = value + rhs if op == "+" else value - rhs
        return value

    def parse_term() -> int:
        """乘层：把若干幂按从左到右的 * 连乘。"""
        nonlocal pos
        value = parse_power()
        while pos < len(s) and s[pos] == "*":
            pos += 1
            value *= parse_power()
        return value

    def parse_power() -> int:
        """幂层：左结合的 ^，即 2^3^2 = (2^3)^2 = 64。"""
        nonlocal pos
        value = parse_atom()
        while pos < len(s) and s[pos] == "^":
            pos += 1
            value **= parse_atom()  # 指数 ≤ 10，快速幂都不需要
        return value

    def parse_atom() -> int:
        """原子：变量 a（代入 x）、括号子表达式或十进制数。"""
        nonlocal pos
        if s[pos] == "a":
            pos += 1
            return x
        if s[pos] == "(":
            pos += 1
            value = parse_expr()
            pos += 1  # 跳过配对的 ')'
            return value
        start = pos
        while pos < len(s) and s[pos].isdigit():
            pos += 1
        return int(s[start:pos])

    return parse_expr()


def same(expr: str, other: str) -> bool:
    """两式在 0,1,2,3 处取值都相同才认定等价（4 次多项式差异即可被识破）。"""
    return all(calc(expr, x) == calc(other, x) for x in range(4))


def solve() -> None:
    lines = sys.stdin.read().splitlines()
    std = lines[0]
    n = int(lines[1])
    picks = [chr(ord("A") + i) for i in range(n) if same(std, lines[2 + i])]
    print("".join(picks))


if __name__ == "__main__":
    solve()
