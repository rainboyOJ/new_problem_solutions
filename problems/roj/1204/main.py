#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:30
# update_at: 2026-09-29 23:30

import sys
from functools import cache


@cache
def ways(n: int) -> int:
    """走完 n 级楼梯的走法数：最后一步跨 1 级或 2 级，二者方案互斥且完备。"""
    return 1 if n <= 1 else ways(n - 1) + ways(n - 2)


def solve() -> None:
    # 每行一个 N，直接逐个求值；@cache 保证每个 N 只算一次
    out = [str(ways(n)) for n in map(int, sys.stdin.buffer.read().split())]
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
