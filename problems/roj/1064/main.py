#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:58
# update_at: 2026-09-29 17:03

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    days = next(data)  # 参与决赛的天数 n，题面保证 1 <= n <= 17

    # 每天固定 3 个整数，按题面顺序读成 n 个三元组，依次是金、银、铜。
    rows = [[next(data), next(data), next(data)] for _ in range(days)]
    # zip(*rows) 是矩阵转置：第 k 个元素恰好是第 k 列（某一种奖牌）的全部取值。
    gold, silver, bronze = map(sum, zip(*rows))
    print(gold, silver, bronze, gold + silver + bronze)  # 第 4 个数是三列之和


if __name__ == "__main__":
    solve()
