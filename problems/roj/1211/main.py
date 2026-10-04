#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:43
# update_at: 2026-09-29 23:43

import sys
from functools import cache
from re import findall


@cache
def in_set(k: int, x: int) -> bool:
    """判断 x 是否在以 k 为种子的集合 M 中：沿 2y+1 / 3y+1 反向收缩。"""
    if x < k:  # 反向操作只会变小，越过种子 k 就再也无法回去了
        return False
    if x == k:
        return True
    reach = False                       # x-1 的前驱：能整除 2 或整除 3 的那一个
    for d in (2, 3):                    # (x-1) 能被 d 整除 → x 可能由 (x-1)/d 生成
        if (x - 1) % d == 0:
            reach = reach or in_set(k, (x - 1) // d)
    return reach


def solve() -> None:
    k, x = map(int, findall(r"\d+", sys.stdin.buffer.read().decode()))  # 统一抓出全部整数
    print("YES" if in_set(k, x) else "NO")


if __name__ == "__main__":
    solve()
