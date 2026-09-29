#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 01:07
# update_at: 2026-09-30 01:07

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                                     # 数组长度，只用来读走 n 个数
    nums = [next(data) for _ in range(n)]
    k = next(data)                                     # 要输出的最大数个数

    # 前 k 大 = 降序排列的前 k 个；无需为 k 的大小分情况，切片天然保留重复元素
    print('\n'.join(map(str, sorted(nums, reverse=True)[:k])))


if __name__ == "__main__":
    solve()
