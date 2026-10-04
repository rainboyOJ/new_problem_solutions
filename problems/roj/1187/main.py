#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:40
# update_at: 2026-10-04 14:35

import sys
from collections import Counter


def solve() -> None:
    """读入字符串，统计 26 个小写字母出现次数，输出次数最多且 ASCII 最小的字符。"""
    data = iter(sys.stdin.buffer.read().split())
    s = next(data).decode()
    cnt = Counter(s)

    # 按出现次数降序、ASCII 升序选出答案字符：max 在次数相同时取 -ord 更大者，即 ASCII 更小者
    ch: str = max(cnt, key=lambda c: (cnt[c], -ord(c)))
    print(ch, cnt[ch])


if __name__ == "__main__":
    solve()
