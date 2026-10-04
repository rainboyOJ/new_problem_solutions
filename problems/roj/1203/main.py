#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:28
# update_at: 2026-09-29 23:28

import sys


def marked_line(s: str) -> str:
    """返回标注行：多余的左括号标 $，多余的右括号标 ?，其余位置留空格。"""
    stack: list[int] = []          # 尚未配对的左括号下标，"距离最近"就是栈顶
    unmatched_right: set[int] = set()
    for i, ch in enumerate(s):
        if ch == '(':
            stack.append(i)
        elif ch == ')':
            if stack:
                stack.pop()        # 与左边最近的未配对左括号配对
            else:
                unmatched_right.add(i)
    unmatched_left = set(stack)    # 扫完仍留在栈里的左括号永远找不到搭档
    return ''.join(
        '$' if i in unmatched_left else '?' if i in unmatched_right else ' '
        for i in range(len(s))
    )


def solve() -> None:
    lines = sys.stdin.read().split()   # 一行一组数据，组间空白分隔
    sys.stdout.write(''.join(f'{s}\n{marked_line(s)}\n' for s in lines))


if __name__ == "__main__":
    solve()
