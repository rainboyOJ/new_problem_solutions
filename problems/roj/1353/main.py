#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:17
# update_at: 2026-10-07 15:28

import sys
from itertools import accumulate

END = '@'                  # 表达式结束标志，它之后的内容（换行、多余空白）一律不看
DELTA = {'(': 1, ')': -1}  # 圆括号对栈高的增量；字母、运算符、空格都不改变栈高


def is_matched(expr: str) -> bool:
    """括号是否匹配：栈高处处非负（没有多余的右括号），且收尾归零（没有多余的左括号）。

    栈里只放左括号，所以"还剩几个左括号"这一个数就够描述状态，不必真的把字符压进栈；
    每个位置上的栈高就是增量的前缀和，收尾栈高恰好等于全部增量之和。
    """
    deltas = [DELTA.get(ch, 0) for ch in expr]                # 每个字符对栈高的增量
    never_negative = all(h >= 0 for h in accumulate(deltas))  # all 一碰到负前缀就短路
    balanced_total = sum(deltas) == 0                         # 总增量 = 左右括号个数之差
    return never_negative and balanced_total


def solve() -> None:
    data = sys.stdin.buffer.read().decode()
    # 表达式内部可能有空格，按 token 读会被切开，所以整行读入后截到 @ 为止
    body = data.partition(END)[0]
    print('YES' if is_matched(body) else 'NO')


if __name__ == "__main__":
    solve()
