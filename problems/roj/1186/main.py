#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:45
# update_at: 2026-10-04 10:18

import sys
from collections import Counter


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 数组大小
    count = Counter(next(data) for _ in range(n))  # 每个值的出现次数
    value, times = max(count.items(), key=lambda kv: kv[1])  # 众数及其次数
    # 超过一半：times / n > 1/2 等价于 2 * times > n，用乘法避免浮点
    print(value if 2 * times > n else "no")


if __name__ == "__main__":
    solve()
