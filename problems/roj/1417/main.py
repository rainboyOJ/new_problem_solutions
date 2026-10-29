#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-29 19:35
# update_at: 2026-10-29 19:35

import sys

NEG_INF = -10**18  # 答案可能为负（价格一路下跌），初值取得足够小


def solve() -> None:
    """一遍扫描维护见过的最低价，对每个卖出时刻算出它能拿到的最大利润。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    min_price = next(data)  # 第 0 个时刻只能当买入点，先把它记为最低价
    ans = NEG_INF

    for _ in range(n - 1):
        price = next(data)
        # 先算利润、再更新最低价，保证买入时刻严格早于卖出时刻
        if price - min_price > ans:
            ans = price - min_price
        if price < min_price:
            min_price = price

    print(ans)


if __name__ == "__main__":
    solve()
