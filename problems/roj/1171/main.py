#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 21:51
# update_at: 2026-10-04 14:44

import sys
from functools import reduce


def mod_by(s: str, k: int) -> int:
    """十进制字符串 s 表示的大整数对 k 取模，逐位递推：r = (r*10 + d) % k。"""
    return reduce(lambda r, ch: (r * 10 + int(ch)) % k, s, 0)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    c = next(data).decode()  # 大整数按十进制字符串读入，mod_by 要逐位取模
    ans = [str(k) for k in range(2, 10) if mod_by(c, k) == 0]
    print(" ".join(ans) if ans else "none")


if __name__ == "__main__":
    solve()
