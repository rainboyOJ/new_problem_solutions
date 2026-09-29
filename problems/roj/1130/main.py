#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:15
# update_at: 2026-09-29 20:15

import sys
from collections import Counter


def solve() -> None:
    s = sys.stdin.buffer.read().strip()
    freq = Counter(s)  # s 是 bytes，迭代得到 0..255 的整数，可直接当下标
    # 频次表备好后再按原串顺序回扫，第一个 freq==1 的字符就是答案；扫完都没有则输出 no
    print(next((chr(c) for c in s if freq[c] == 1), "no"))


if __name__ == "__main__":
    solve()
