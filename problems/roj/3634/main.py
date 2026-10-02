#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 11:56
# update_at: 2026-10-02 11:56

import sys

data = map(int, sys.stdin.read().split())


def cost(n: int, qty: int, price: int) -> int:
    """整包买至少 n 支该包装铅笔的花费：不够一包也要按一整包算。"""
    return (n + qty - 1) // qty * price  # 向上取整的份数 × 单包价格


def solve() -> None:
    n = next(data)
    packs = [(next(data), next(data)) for _ in range(3)]  # 三种包装：(数量, 价格)
    print(min(cost(n, qty, price) for qty, price in packs))


if __name__ == "__main__":
    solve()
