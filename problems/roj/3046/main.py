#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:55
# update_at: 2026-10-01 11:54

import sys

PAIR = {')': '(', ']': '[', '}': '{'}  # 右括号 → 它唯一能配上的左括号


def longest_valid(s: str) -> int:
    """最长的合法括号子段长度：栈里只存尚未配对的左括号下标。"""
    ans = 0
    stack: list[int] = []
    barrier = -1  # 最近一个无法配对的右括号下标，合法子段不可能跨过它
    for i, ch in enumerate(s):
        opener = PAIR.get(ch)
        if opener is None:  # 左括号：下标入栈，等待将来的右括号
            stack.append(i)
        elif stack and s[stack[-1]] == opener:
            # 与栈顶左括号配对：以 i 结尾的合法子段，左端紧贴"栈内更靠下的
            # 未配对左括号"或壁垒，二者之间恰好是一段合法序列
            stack.pop()
            left = stack[-1] if stack else barrier
            ans = max(ans, i - left)
        else:
            # 配不上的右括号：任何包含它的子段都非法，它成为新壁垒，
            # 且它之前入栈的左括号再也配不上（配对不能交叉），清空栈
            stack.clear()
            barrier = i
    return ans


def solve() -> None:
    s = sys.stdin.read().strip()
    print(longest_valid(s))


if __name__ == "__main__":
    solve()
