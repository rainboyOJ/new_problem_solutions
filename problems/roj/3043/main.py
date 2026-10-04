#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:52
# update_at: 2026-10-01 11:52

import sys
from collections.abc import Iterator
from heapq import heappop, heappush

DOS_EOF = b'\x1a'  # 老数据文件的 DOS 结束符，当作空白丢弃


def best_profit(deals: list[tuple[int, int]]) -> int:
    """deals 里每项是 (过期时间 d, 利润 p)，返回这一组商品的最大收益。

    按 d 升序扫描，堆里只装"暂定要卖"的利润，堆的大小就是这些商品占用的天数：
    截至第 d 天最多卖出 d 件，所以处理完过期时间为 d 的一批后，堆若超过 d 个，
    就弹出最小的那个利润——它被放弃，换来的名额留给更值钱的商品。
    """
    heap: list[int] = []
    for d, p in sorted(deals):          # 元组比较先看 d，天然按过期时间升序
        heappush(heap, p)
        if len(heap) > d:               # 第 1..d 天一共只有 d 个摊位
            heappop(heap)               # 忍痛丢掉利润最小的那件
    return sum(heap)


def solve() -> None:
    raw = sys.stdin.buffer.read().replace(DOS_EOF, b' ')
    data: Iterator[int] = iter(map(int, raw.split()))
    out: list[str] = []

    for n in data:                      # 每组用例以 N 开头，读到文件结尾为止
        deals: list[tuple[int, int]] = []
        for _ in range(n):
            p, d = next(data), next(data)   # 题面顺序：先利润 p_i，后过期时间 d_i
            deals.append((d, p))
        out.append(str(best_profit(deals)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
