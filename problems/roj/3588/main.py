#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 09:30
# update_at: 2026-10-02 09:30

import sys


def cover(x: int, y: int, a: int, b: int, g: int, k: int) -> bool:
    """点 (x, y) 是否在地毯 [a, a+g] × [b, b+k] 内（含边界）。"""
    return a <= x <= a + g and b <= y <= b + k


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 按铺设顺序存下每张地毯；从最后一张往前找，第一个覆盖查询点的就是最上面的。
    carpets = [(next(data), next(data), next(data), next(data)) for _ in range(n)]
    x, y = next(data), next(data)

    for i in range(n - 1, -1, -1):
        a, b, g, k = carpets[i]
        if cover(x, y, a, b, g, k):
            print(i + 1)  # 地毯编号从 1 开始
            return
    print(-1)


if __name__ == "__main__":
    solve()
