#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:39
# update_at: 2026-09-29 20:39

import re


def reverse_words(line: str) -> str:
    r"""逐词反转：\S+ 只命中连续非空白段（单词），段外空白不参与匹配、原样保留。"""
    return re.sub(r"\S+", lambda seg: seg.group()[::-1], line)


def solve() -> None:
    line = input()  # 只有一行；input() 只去行末换行，行内空格是内容不是分隔符
    print(reverse_words(line))


if __name__ == "__main__":
    solve()
