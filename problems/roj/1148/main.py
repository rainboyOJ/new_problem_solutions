#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:49
# update_at: 2026-09-29 20:49

import sys

NO_ANSWER = "No"  # 不存在满足条件的字符时的输出


def first_repeat_char(s: str, k: int) -> str:
    """回答：字符串中第一个"连续出现至少 k 次"的字符；没有则回答 No。

    与标准程序一致的处理顺序：位置 i 处先看前一段是否已凑满 k 个，
    再把 s[i] 并入当前段。这样末尾凑满 k 的段不会再触发（其后无元素），
    k=1 时输出第一个"与前一个相同"的字符。
    """
    run = 0
    for i, ch in enumerate(s):
        if run == k:  # 前一段已连续出现 k 次，段尾字符即答案
            return ch
        can_continue = i + 1 < len(s) and s[i + 1] == ch  # s[i] 后面还跟着同字符
        run = run + 1 if can_continue else 1              # 否则当前段从 1 重新数起
    return NO_ANSWER


def solve() -> None:
    k, s = sys.stdin.read().split()  # 次数门槛 k 与待查字符串 s

    print(first_repeat_char(s, int(k)))


if __name__ == "__main__":
    solve()
