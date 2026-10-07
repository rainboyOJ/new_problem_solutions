#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:14
# update_at: 2026-10-07 15:14

import sys
from functools import cache


@cache
def ways(m: int, n: int) -> int:
    """把 m 个相同苹果放进 n 个相同盘子（允许空盘）的分法数。"""
    if m == 0:
        return 1                              # 苹果已放完，剩下的盘子只能空着
    if n == 0:
        return 0                              # 没有盘子，剩下的苹果无处可放
    if n > m:
        return ways(m, m)                     # 盘子多于苹果，多出来的盘子必然空着
    return ways(m, n - 1) + ways(m - n, n)    # 至少一个空盘 + 每盘先放一个再分剩下的


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(data, 0)                         # 测试数据组数；空输入按 0 组处理

    out: list[str] = []
    for _ in range(t):
        m, n = next(data), next(data)         # 本组询问的两个量
        out.append(str(ways(m, n)))

    if out:                                   # t = 0 时题目要求输出为空，不能多一个换行
        print('\n'.join(out))


if __name__ == "__main__":
    solve()
