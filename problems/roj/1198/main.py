#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:05
# update_at: 2026-09-29 23:05

import sys
from collections.abc import Iterator


def eval_expr(tokens: Iterator[str]) -> float:
    """递归求值前缀表达式：当前 token 是运算符则取左右子式，否则为数字。"""
    tok = next(tokens)
    if tok in "+-*/":
        left = eval_expr(tokens)
        right = eval_expr(tokens)
        if tok == "+":
            return left + right
        if tok == "-":
            return left - right
        if tok == "*":
            return left * right
        return left / right
    return float(tok)


def solve() -> None:
    data = sys.stdin.buffer.read().decode().split()
    tokens = iter(data)
    ans = eval_expr(tokens)
    print(f"{ans:.6f}")


if __name__ == "__main__":
    solve()
