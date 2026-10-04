#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 06:53
# update_at: 2026-09-30 06:56

import sys

PAIRS = {')': '(', ']': '['}  # 右括号 → 它唯一能配的那个左括号
OPEN = frozenset(PAIRS.values())  # 左括号集合
WIDE = str.maketrans('（）［］', '()[]')  # 题面样例用的是全角括号，先折算成 ASCII 再判断


def is_matched(brackets: str) -> bool:
    """括号串是否匹配：右括号只允许消耗栈顶那个同类左括号，扫完后栈必须为空。"""
    stack: list[str] = []  # 尚未闭合的左括号，栈底在外层、栈顶在最内层
    for ch in brackets:
        if ch in OPEN:
            stack.append(ch)  # 左括号入栈，等它对应的右括号
        elif not stack or stack[-1] != PAIRS[ch]:
            return False  # 弹空（右括号多了），或栈顶是与它不同类的左括号
        else:
            stack.pop()  # 配对成功，最内层这一层闭合
    return not stack  # 栈非空说明还有左括号没被配对


def solve() -> None:
    raw = sys.stdin.buffer.read()
    # 数据仓里既有 CRLF 的 ASCII 行，也可能有带 BOM 的 UTF-16 行，先按字节识别再整体解码
    text = raw.decode('utf-16') if raw.startswith((b'\xff\xfe', b'\xfe\xff')) else raw.decode(errors='ignore')
    # 括号以外的字符（空格、换行等）与匹配无关，一次性滤掉
    brackets = ''.join(ch for ch in text.translate(WIDE) if ch in OPEN or ch in PAIRS)
    print("OK" if is_matched(brackets) else "Wrong")


if __name__ == "__main__":
    solve()
