#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:52
# update_at: 2026-10-02 13:52

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n = next(data)
        coins = sorted(next(data) for _ in range(n))
        top = coins[-1]             # 只需关心 [0, top] 内的金额：查询都落在面额上
        mask = (1 << (top + 1)) - 1
        reachable = 1               # 第 0 位为 1：金额 0 用 0 张货币即可表出
        basis = 0

        for coin in coins:
            already = reachable >> coin & 1
            if not already:         # 更小面额表不出 coin → 等价系统必须保留它
                basis += 1
                # 无限张 coin 的闭包：旧可达集合整体平移 k*coin（k≥1）后并回
                closed = reachable
                shift = coin
                while shift <= top:
                    closed |= reachable << shift
                    shift += coin
                reachable = closed & mask

        out.append(str(basis))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
