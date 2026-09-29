#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:35
# update_at: 2026-09-29 19:43

import sys

# 十种图书的单价，单位是「角」，顺序与题面的购买数量一一对应
PRICES_IN_JIAO: tuple[int, ...] = (289, 327, 456, 780, 350, 862, 278, 430, 560, 650)


def solve() -> None:
    counts = map(int, sys.stdin.buffer.read().split())  # 十个购买数量
    # 单价都是一位小数，按「角」做整数加权和可以全程无舍入；只在输出时换回元
    total_in_jiao = sum(price * count for price, count in zip(PRICES_IN_JIAO, counts))
    print(f"{total_in_jiao / 10:.1f}")  # 四舍五入到一位小数，并固定补足这一位


if __name__ == "__main__":
    solve()
