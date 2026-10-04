#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def split_pieces(stock: int) -> list[int]:
    """把最大购买量 stock 拆成 1,2,4,... 的二进制份：任取 0..stock 件都能由若干份凑出。"""
    pieces: list[int] = []
    k = 1
    while k <= stock:
        pieces.append(k)
        stock -= k
        k <<= 1
    if stock:
        pieces.append(stock)  # 拆剩下的余数单独成一份
    return pieces


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)  # n 种奖品，拨款 m

    dp = [0] * (m + 1)  # dp[j]：预算不超过 j 时能取得的最大总价值
    for _ in range(n):
        price, value, stock = next(data), next(data), next(data)
        for piece in split_pieces(stock):
            cost = piece * price  # 这一份捆绑的整体价格
            if cost > m:
                break             # 二进制份只会越来越大，后面的份必然也超预算
            gain = piece * value  # 这一份捆绑的整体价值
            # 0/1 背包：dp[j] = max(dp[j], dp[j-cost]+gain)；两侧读的都是旧值
            dp[cost:] = map(max, dp[cost:], (old + gain for old in dp))

    print(dp[m])


if __name__ == "__main__":
    solve()
