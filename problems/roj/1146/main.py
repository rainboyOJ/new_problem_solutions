#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:49
# update_at: 2026-09-29 20:49

import sys


def solve() -> None:
    text = sys.stdin.read().strip()   # 整行即整串，题面保证串内没有空白字符
    mirrored = text[::-1]             # 一次切片反转，倒读串由 C 层循环生成
    same = text == mirrored           # 回文 ⟺ 正读与倒读逐位相同
    print("yes" if same else "no")


if __name__ == "__main__":
    solve()
