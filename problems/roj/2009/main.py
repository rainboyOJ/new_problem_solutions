#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:03
# update_at: 2026-10-08 07:03

import sys


def greedy_cost(need: int, farmers: list[tuple[int, int]]) -> int:
    """按单价从低到高采购，返回凑满 need 加仑的最小花费。"""
    remain = need  # 还差多少牛奶没买到
    cost = 0       # 累计花费，量级 2e6 * 1000，Python 大整数天然安全
    for price, amount in sorted(farmers):  # 元组比较，主键就是单价
        if remain <= 0:
            break  # 需求已满足（含 need = 0 的边界）
        take = min(amount, remain)  # 剩下的第一个人只需买一部分
        cost += take * price
        remain -= take
    return cost


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    need, m = next(data), next(data)
    farmers = [(next(data), next(data)) for _ in range(m)]  # (价格 P_i, 供应量 A_i)
    print(greedy_cost(need, farmers))


if __name__ == "__main__":
    solve()
