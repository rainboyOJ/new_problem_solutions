#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:19
# update_at: 2026-10-02 07:19

import sys
from collections import Counter


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 自然数的总个数（含重复）
    # 计数后按值升序输出：Counter 一次扫描，排序代价只与不同数个数（≤1e4）相关
    counter = Counter(data)  # 剩余 n 个数全部喂给计数器
    out = [f"{value} {counter[value]}" for value in sorted(counter)]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
