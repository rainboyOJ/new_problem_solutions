#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:10
# update_at: 2026-10-01 21:10

import re
import sys
from array import array
from collections import deque

NUMBER_RE = re.compile(rb"\d+")  # 题面只出现非负整数，按数字串切分比 split 省一大半内存


def parse_chain() -> tuple[array, int]:
    """读入仓库数 n 与库存 A，返回“断环成链”后的库存序列以及窗口允许的最大下标差。"""
    buf = sys.stdin.buffer.read()
    values = array("i", (int(m.group()) for m in NUMBER_RE.finditer(buf)))
    del buf                                        # 原始字节只用于切分，尽早释放
    n = values[0]
    reach = n // 2                                 # 环上每一对仓库总有一个方向距离不超过 n // 2
    chain = values[1:n + 1] + values[1:1 + reach]  # 跨过编号 n 的那一对也落进同一条链
    del values
    return chain, reach


def best_cost(chain: array, reach: int) -> int:
    """求链上 max(A[i] + A[j] + (j - i))，只保留下标差 1 <= j - i <= reach 的配对。

    距离并进点权后，右端点 j 只需在滑动窗口 [j - reach, j - 1] 里问
    “谁的 A[i] - i 最大”，取窗口最大值正是单调队列的职责。
    """
    queue: deque[int] = deque()  # 存左端点下标，链上权值 A[i] - i 从队首到队尾严格递减
    best = 0                     # A[i] >= 1，所以 0 是安全的初值，n = 1 时直接输出它
    for j in range(1, len(chain)):
        i = j - 1                                     # j 左边最近的仓库，一定在窗口内
        weight = chain[i] - i                         # 该左端点的 f(i)
        while queue and chain[queue[-1]] - queue[-1] <= weight:
            queue.pop()                               # 队尾更小又更早过期，不再可能当选
        queue.append(i)
        while queue[0] < j - reach:                   # 距离超过 reach 的左端点滑出窗口
            queue.popleft()
        cost = chain[queue[0]] - queue[0] + chain[j] + j
        if cost > best:
            best = cost
    return best


def solve() -> None:
    chain, reach = parse_chain()  # n = 1 时链长为 1，扫描循环不执行，答案就是 best 的初值 0
    print(best_cost(chain, reach))


if __name__ == "__main__":
    solve()
