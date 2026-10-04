#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 16:45
# update_at: 2026-09-29 16:52

import sys
from itertools import islice


def solve() -> None:
    data = map(int, sys.stdin.buffer.read().split())  # map 已经是迭代器，可 next 消费
    n = next(data)                     # 学生人数，同时是要求和的元素个数
    ages = islice(data, n)             # 紧跟其后的 n 个年龄，惰性取出即可求和
    print(f"{sum(ages) / n:.2f}")      # 保留两位小数，对齐参考实现的 "%.2lf"


if __name__ == "__main__":
    solve()
