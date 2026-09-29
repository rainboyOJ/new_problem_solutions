#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-03 11:23
# update_at: 2026-07-03 11:23

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    stock = next(data, 0)          # 药房当前剩余库存
    patients = next(data, 0)       # 取药人数
    rejected = 0

    for amount in data:            # 按时间顺序处理每个病人的取药请求
        if stock >= amount:        # 库存足够，发药并扣减库存
            stock -= amount
        else:                      # 库存不足，拒绝该病人
            rejected += 1

    print(rejected)


if __name__ == "__main__":
    solve()
