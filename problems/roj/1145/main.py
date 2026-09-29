#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:20
# update_at: 2026-09-29 21:20

import sys
from itertools import groupby


def encode(text: str) -> str:
    """把原串压成 p 型编码串：每个连续段输出「段长 + 该数字」。

    题目例子 122344111 → 1个1、2个2、1个3、2个4、3个1 → 1122132431，
    也就是对每个极大同字符段依次写出 len(段) 与段字符。
    """
    return "".join(f"{len(list(run))}{digit}" for digit, run in groupby(text))


def solve() -> None:
    text = sys.stdin.read().strip()   # 整行即整串，题面保证串内没有空白字符
    print(encode(text))


if __name__ == "__main__":
    solve()
