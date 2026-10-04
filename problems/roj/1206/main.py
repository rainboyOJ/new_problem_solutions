#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:27
# update_at: 2026-09-29 23:27

import sys
from functools import cache


@cache
def ways(apples: int, plates: int) -> int:
    """m 个苹果放进 n 个相同盘子（可空）的分法数，按"有没有空盘"分类。"""
    if apples == 0:
        return 1  # 苹果放完：所有盘子都空着，只有一种分法
    if plates == 0:
        return 0  # 苹果没放完却没盘子了，无解
    if plates > apples:
        return ways(apples, apples)  # 多余盘子必空，等价于只用 m 个盘子
    # 不用第 n 个盘子 ways(m, n-1)；第 n 个盘子至少放一个，先扣掉再递归
    return ways(apples, plates - 1) + ways(apples - plates, plates)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data)  # 询问组数
    print('\n'.join(str(ways(next(data), next(data))) for _ in range(t)))


if __name__ == "__main__":
    solve()
