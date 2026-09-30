#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:00
# update_at: 2026-09-30 17:00

import sys
from collections import defaultdict


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    wires = [(next(data), next(data)) for _ in range(m)]  # 每根导线两端，端点为 0 表示自由端

    # 并查集：把同一焊点上的导线并成一个连通块。端点 0 不是焊点，不参与合并。
    parent = list(range(n + 1))

    def find(x: int) -> int:
        """返回 x 所在连通块的代表元，路径压缩。"""
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    for a, b in wires:
        if a and b:
            ra, rb = find(a), find(b)
            if ra != rb:
                parent[ra] = rb

    # 每个连通块累计三件事：奇数度焊点数、自由端数、度数 > 2 的焊点数。
    # 度数从导线端点统计，节点 0 单独记成"自由端"。
    deg: dict[int, int] = defaultdict(int)
    blocks: dict[object, list[int]] = defaultdict(lambda: [0, 0, 0])  # [odd, free, high]
    for i, (a, b) in enumerate(wires):
        if a and b:
            key = find(a)
        elif a:
            key = find(a)
        elif b:
            key = find(b)
        else:
            key = ("lone", i)  # 两端都自由的导线自己就是一个连通块
        blocks[key][1] += (a == 0) + (b == 0)
    for a, b in wires:
        for x in (a, b):
            if x:
                deg[x] += 1
    for v, d in deg.items():
        blocks[find(v)][0] += d % 2
        blocks[find(v)][2] += d > 2

    # 每个连通块独立算代价再求和：
    # 奇端数 o 必须两两焊接，贡献 o/2 次焊接；度数 > 2 的焊点要烧熔拆开，贡献 high 次。
    # o == 0 说明它本身已经闭合成环，要先烧开再焊回去，代价至少 2。
    total = 0
    for odd, free, high in blocks.values():
        o = odd + free
        total += high + o // 2 if o else max(2, high + 1)

    print(total)


if __name__ == "__main__":
    solve()
