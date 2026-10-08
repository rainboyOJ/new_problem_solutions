#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 00:01
# update_at: 2026-10-09 00:09

import sys


def contains_after_shift(s1: str, s2: str) -> bool:
    """s1 的某个循环移位串是否包含 s2：长者作母串，倍增一次后查短串。"""
    if len(s1) < len(s2):
        s1, s2 = s2, s1       # 长度守卫：|s2| > |s1| 时短串绝不可能包含长串，排除假阳性
    return s2 in s1 + s1      # s1 + s1 把全部 |s1| 个循环移位展开在同一条串上


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    s1 = next(data, None)
    s2 = next(data, None)
    if s1 is None or s2 is None:     # 缺参数：安静退出，与 C++ 侧一致
        return

    print("true" if contains_after_shift(s1.decode(), s2.decode()) else "false")


if __name__ == "__main__":
    solve()
