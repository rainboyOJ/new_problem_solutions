#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 00:57
# update_at: 2026-09-30 01:04

import sys
from collections.abc import Iterable
from heapq import heapify, heapreplace


def finish_time(loads: list[int], taps: int) -> int:
    """返回所有人接完水的总秒数。

    规则等价于：新人补到"累计接水量最小"的龙头（它最先空出来，其它龙头都还在忙）。
    题面直接规定了落点，没有需要搜索的目标；龙头不空转，所以每个龙头的完工时刻就是
    分给它的 w 之和，答案取这些累计量的最大值。堆里存的就是各龙头的累计接水量。
    """
    earliest = loads[:taps]  # 前 taps 个人先各占一个龙头；n < m 时堆自然更小
    heapify(earliest)
    for load in loads[taps:]:
        heapreplace(earliest, earliest[0] + load)  # 最早空出的龙头立刻接这位同学
    return max(earliest, default=0)


def solve() -> None:
    """读入 n、m 和 n 个接水量，输出总接水时间。"""
    data: Iterable[bytes] = iter(sys.stdin.buffer.read().split())
    n, m = int(next(data)), int(next(data))
    loads = [int(next(data)) for _ in range(n)]
    print(finish_time(loads, m))


if __name__ == "__main__":
    solve()
