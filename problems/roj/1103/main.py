#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:55
# update_at: 2026-09-29 18:55

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    apples = [next(data) for _ in range(10)]  # 题面固定 10 个苹果离地高度（cm）
    reach = next(data) + 30                   # 伸手最大高度 + 30cm 板凳 = 实际够到高度
    print(sum(h <= reach for h in apples))    # 碰到即掉：高度不超过 reach 就能摘


if __name__ == "__main__":
    solve()
