#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:51
# update_at: 2026-09-30 06:58

import sys

# 左括号按“允许的嵌套层级”编码：编号越大越靠内层。
# 题面要求从内到外依次是 <>, (), [], {}，所以 < 必须在最内层（编号 3），{ 在最外层（编号 0）。
# 右括号编码 = 同类左括号 + 4，于是“左右是否同一种括号”退化成“编码差是否为 4”。
LEVEL = {'{': 0, '[': 1, '(': 2, '<': 3, '}': 4, ']': 5, ')': 6, '>': 7}
CLOSE = 4  # 互相匹配的一对括号，其左、右编码的固定差值


def is_matched(s: str) -> bool:
    """判断一行括号串是否合法：必须两两配对，且从内到外依次是 <>,(),[],{}。"""
    stack: list[int] = []  # 自底向上只存左括号编号，恰好对应“由外到内”的嵌套顺序
    for code in map(LEVEL.get, s):
        if code < CLOSE:  # 左括号
            if stack and code < stack[-1]:  # 编号比当前最内层还小，也就是还想更靠外
                return False
            stack.append(code)
        elif not stack:  # 右括号，但没有可配对的左括号
            return False
        else:
            top = stack.pop()
            if code - top != CLOSE:  # 与刚弹出的左括号不同种
                return False
    return not stack  # 还留着没闭合的左括号时栈非空


def solve() -> None:
    lines = sys.stdin.read().splitlines()
    n = int(lines[0])  # 第一行是串数
    answers = ('YES' if is_matched(line.strip()) else 'NO' for line in lines[1:1 + n])
    print('\n'.join(answers))


if __name__ == "__main__":
    solve()
