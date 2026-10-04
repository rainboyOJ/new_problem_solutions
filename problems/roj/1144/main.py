#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:39
# update_at: 2026-10-04 14:36

import re
import sys


def reverse_words(line: str) -> str:
    r"""逐词反转：\S+ 只命中连续非空白段（单词），段外空白不参与匹配、原样保留。"""
    return re.sub(r"\S+", lambda seg: seg.group()[::-1], line)


def solve() -> None:
    data = iter(sys.stdin.read().splitlines())  # 一行一个元素，不切分 token
    line = next(data)  # 空格是内容不是分隔符：逐行产出才能整行拿到，行内空格原样保留
    print(reverse_words(line))


if __name__ == "__main__":
    solve()
