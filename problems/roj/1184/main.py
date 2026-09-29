#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:38
# update_at: 2026-09-29 22:38

import sys

MAX_VALUE = 1000  # 题面保证每个随机数都在 [1, 1000]，桶的下标就是随机数本身


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    bucket = bytearray(MAX_VALUE + 1)  # 桶：bucket[v] = 1 表示数字 v 出现过
    for token in data[1:]:             # 第 0 个 token 是数量 N，之后才是随机数
        bucket[int(token)] = 1         # 重复的数字写进同一个格子，去重自动完成
    unique = [v for v in range(1, MAX_VALUE + 1) if bucket[v]]  # 按下标扫描 = 已排好序
    print(len(unique))
    print(*unique)


if __name__ == "__main__":
    solve()
