#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:05
# update_at: 2026-09-29 19:05

import sys

# 四个年龄段的右端点（19-35、36-60、61 以上），0-18 单独算：年龄 ≤ 右端点的第一个桶
BOUNDS = [18, 35, 60]


def bucket(age: int) -> int:
    """返回年龄所属桶：0=0-18，1=19-35，2=36-60，3=61 以上。"""
    return sum(age > bound for bound in BOUNDS)  # 越过几个右端点就是第几桶


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    counts = [0, 0, 0, 0]
    for _ in range(n):
        age = next(data)
        counts[bucket(age)] += 1

    print('\n'.join(f'{count * 100 / n:.2f}%' for count in counts))


if __name__ == "__main__":
    solve()
