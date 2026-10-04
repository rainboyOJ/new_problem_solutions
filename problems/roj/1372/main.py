#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:30
# update_at: 2026-09-30 07:30

import sys
from collections import Counter
from heapq import heappop, heappush


def clean_top(heap: list[int], cnt: Counter[int]) -> None:
    """反复弹出已付清面额的堆顶，直到堆顶是池里还没付的账单。"""
    while cnt[abs(heap[0])] == 0:  # 账单付掉时只减计数，堆里留到此刻才真正删除
        heappop(heap)


def pay_extremes(lo: list[int], hi: list[int], cnt: Counter[int]) -> tuple[int, int]:
    """付出账单池里面额最小和最大的两张，返回这两个面额。"""
    clean_top(lo, cnt)
    clean_top(hi, cnt)
    low, high = lo[0], -hi[0]  # hi 存相反数，取负还原面额
    cnt[low] -= 1
    cnt[high] -= 1
    return low, high


def solve() -> None:
    inp = sys.stdin.buffer.readline
    n = int(inp())               # 补卡天数
    cnt: Counter[int] = Counter()  # 面额 -> 未支付张数（懒删除的记账本）
    lo: list[int] = []           # 面额小根堆
    hi: list[int] = []           # 面额相反数的小根堆，即面额大根堆
    out: list[str] = []

    for _ in range(n):
        parts = inp().split()
        m = int(parts[0])        # 当天新增账单数
        for v in map(int, parts[1:m + 1]):
            cnt[v] += 1
            heappush(lo, v)
            heappush(hi, -v)
        low, high = pay_extremes(lo, hi, cnt)
        out.append(f'{low} {high}')

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
