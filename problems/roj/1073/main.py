#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-01-12 11:20
# update_at: 2026-01-12 11:20

import math
import sys
from collections.abc import Iterator


def read_triples(data: Iterator[str]) -> Iterator[tuple[float, float, int]]:
    """依次读出每个屋顶的横坐标、纵坐标、人数。"""
    while True:
        try:
            x, y, c = next(data), next(data), next(data)
            yield float(x), float(y), int(c)
        except StopIteration:
            return


def rescue_time(x: float, y: float, c: int) -> float:
    """单次往返救援一个屋顶的耗时：往返航行 + 上下船。"""
    dist = math.hypot(x, y)          # 大本营到屋顶的欧氏距离
    sail = dist / 50.0               # 单程航行时间（分钟）
    return 2.0 * sail + 1.5 * c      # 往返 + 每人上船 1 分钟、下船 0.5 分钟


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))              # 屋顶数，仅用于完整性检查
    total = sum(rescue_time(x, y, c) for x, y, c in read_triples(data))
    print(math.ceil(total))


if __name__ == "__main__":
    solve()
