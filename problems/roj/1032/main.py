#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 15:03
# update_at: 2026-09-29 15:03

import math
import sys

THIRST = 20_000  # 大象要解渴需 20 升 = 20000 立方厘米（1 升 = 1000 cm³）


def bucket_count(depth: int, radius: int) -> int:
    """一桶水的立方厘米数能装满几桶才够 20000 cm³：向上取整。"""
    volume = math.pi * radius * radius * depth  # 圆柱体积 πr²h
    return math.ceil(THIRST / volume)


def solve() -> None:
    depth, radius = map(int, sys.stdin.buffer.read().split())
    print(bucket_count(depth, radius))


if __name__ == "__main__":
    solve()
