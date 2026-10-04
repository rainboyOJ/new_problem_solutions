#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys
from functools import reduce
from operator import mul

MOD = 47


def name_score(name: str) -> int:
    """计算名字所有字母对应数值（A=1..Z=26）的乘积模 47 的值。"""
    return reduce(mul, (ord(ch) - ord('A') + 1 for ch in name), 1) % MOD


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    first_name = next(data, b"").decode()
    if not first_name:
        return
    second_name = next(data).decode()
    is_matched = name_score(first_name) == name_score(second_name)
    print("GO" if is_matched else "STAY")


if __name__ == "__main__":
    solve()
