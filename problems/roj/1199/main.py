#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:06
# update_at: 2026-09-29 23:06

import sys
from itertools import permutations


def solve() -> None:
    s = sys.stdin.buffer.read().split()[0].decode()

    # 输入串已按字母序排好：permutations 逐位按下标从小到大取字符，
    # 同一层先试小下标（小字母），故生成顺序天然就是字典序，无需排序。
    print(*map(''.join, permutations(s)), sep='\n')


if __name__ == "__main__":
    solve()
