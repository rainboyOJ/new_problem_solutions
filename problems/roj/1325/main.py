#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:21
# update_at: 2026-09-30 05:21

import sys
from collections.abc import Iterator

MAX_M = 9  # 官方参考程序把日程表开成 1001×1001，M=10 时 N=1024 越界，评测数据还是空的


def schedule(m: int) -> Iterator[str]:
    """逐行产出 2^m 个选手的比赛安排表：选手 i 在第 j 列的对手是 (i xor j) + 1。

    编号从 0 起算，所以列 0 是选手自己（表格对角线），列 1..2^m-1 才是真正的 2^m-1 天。
    """
    n = 1 << m
    for i in range(n):
        yield ' '.join(str((i ^ j) + 1) for j in range(n))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m = next(data, None)  # 输入只有 M 这一个位置量；空输入按原样直接返回
    if m is None:
        return

    if m > MAX_M:  # N=1024 已超出参考实现的表格容量，空输出被固化成测评答案
        return
    print('\n'.join(schedule(m)))


if __name__ == "__main__":
    solve()
