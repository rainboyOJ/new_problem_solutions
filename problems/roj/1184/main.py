#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:38
# update_at: 2026-09-29 22:38

import sys

MAX_VALUE = 1000  # 题面保证每个随机数都在 [1, 1000]，桶的下标就是随机数本身


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                                  # 随机数个数，只决定读多少 token
    bucket = bytearray(MAX_VALUE + 1)               # 桶：bucket[v] = 1 表示数字 v 出现过
    for _ in range(n):                              # 顺序消费接下来的 n 个随机数
        bucket[next(data)] = 1                      # 重复的数字写进同一个格子，去重自动完成
    unique = [v for v in range(1, MAX_VALUE + 1) if bucket[v]]  # 按下标扫描 = 已排好序
    print(len(unique))
    print(*unique)


if __name__ == "__main__":
    solve()
