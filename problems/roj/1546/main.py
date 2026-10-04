#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:25
# update_at: 2026-09-30 17:25

import sys
from collections.abc import Iterator


def read_inns(count: int) -> Iterator[tuple[int, int]]:
    """逐行产出 (色调, 最低消费)：边读边消耗，不把 n 行一次性读进内存。"""
    readline = sys.stdin.buffer.readline
    for _ in range(count):
        color, price = map(int, readline().split())
        yield color, price


def count_pairs(inns: Iterator[tuple[int, int]], k: int, p: int) -> int:
    """统计合法住宿方案数：两店同色，且它们之间（含端点）存在消费 <= p 的咖啡店。

    消费 <= p 的咖啡店会把它之后（含自己）的所有客栈变成"合法左端点"，所以
    合法方案数 = 出现过的同色客栈数 - 还没被便宜咖啡店覆盖到的同色客栈数；
    后者记在欠账 pend 里，碰到便宜咖啡店就一笔清零。
    """
    total = [0] * k            # 各色调出现过的客栈数：历史左端点候选总数
    pend: dict[int, int] = {}  # 欠账：尚未被便宜咖啡店覆盖的客栈，按色调计数
    ans = 0
    for color, price in inns:
        cheap = price <= p
        if cheap:
            pend.clear()                    # 本店咖啡店够便宜：欠账全部转为合法
        uncovered = pend.get(color, 0)      # 刚清零时恒为 0，两种分支可共用
        ans += total[color] - uncovered     # 同色前缀里合法的左端点数量
        total[color] += 1
        if not cheap:
            pend[color] = uncovered + 1     # 本店自己还欠着，记一笔
    return ans


def solve() -> None:
    n, k, p = map(int, sys.stdin.buffer.readline().split())
    print(count_pairs(read_inns(n), k, p))


if __name__ == "__main__":
    solve()
