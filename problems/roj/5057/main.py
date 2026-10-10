#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 01:04
# update_at: 2026-10-09 01:13

import sys

LIGHT_LIMIT = 20.0  # 重量不超过它（含）按低价计费
LIGHT_RATE = 1.68   # 低价单价（元/公斤）
HEAVY_RATE = 1.98   # 超重单价（元/公斤），超重时对【全部重量】适用


def solve() -> None:
    """读入行李重量，按整重单价计费并保留 2 位小数输出。"""
    tokens = sys.stdin.buffer.read().split()  # 只看第一个数，对应 main.cpp 的 cin >> weight
    if not tokens:
        return  # 无输入时不输出，与 main.cpp / std.cpp 一致
    weight = float(tokens[0])
    rate = LIGHT_RATE if weight <= LIGHT_LIMIT else HEAVY_RATE
    print(f"{weight * rate:.2f}")


if __name__ == "__main__":
    solve()
