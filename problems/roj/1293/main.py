#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 03:41
# update_at: 2026-09-30 03:41

import sys

PRICES = (10, 20, 50, 100)  # 四种书价，即完全背包的物品体积


def count_plans(n: int) -> int:
    """恰好花 n 元的买书方案数：f[j] 表示恰好凑出 j 元的方式数。"""
    f = [1] + [0] * n  # f[0] = 1：一种书都不选也是"凑出 0 元"的初始状态
    for price in PRICES:
        for money in range(price, n + 1):  # 正序扫：同一本书可重复购买
            f[money] += f[money - price]
    return f[n]


def solve() -> None:
    n = int(sys.stdin.buffer.read())
    # 样例规定 n = 0 时答案为 0：钱数非 10 的倍数时 f[n] 自然为 0，无需特判
    print(count_plans(n) if n > 0 else 0)


if __name__ == "__main__":
    solve()
