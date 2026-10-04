#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:56
# update_at: 2026-09-30 05:56

import sys
from collections import defaultdict
from collections.abc import Iterator


def pairs(nums: Iterator[int]) -> Iterator[tuple[int, int]]:
    """把 2m 个结点编号按 (父结点, 孩子) 两两成对。"""
    return zip(nums, nums)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 树里每个结点至多一个父亲，某结点的父亲是谁是唯一信息：用 dict 当 parent 数组，
    # 没在右端出现过的编号（get 返回 None）就是根。
    parent: dict[int, int] = {}
    children: dict[int, list[int]] = defaultdict(list)
    for x, y in pairs(data):  # 每行的 y 是 x 的孩子：x 的出边多一条，y 认下父亲 x
        parent[y] = x
        children[x].append(y)

    root = next(v for v in range(1, n + 1) if v not in parent)
    # max 只保留第一个最大值，而 range 递增，所以并列时自然取到编号小的结点。
    busiest = max(range(1, n + 1), key=lambda v: len(children[v]))

    print(root)
    print(busiest)
    print(*sorted(children[busiest]))


if __name__ == "__main__":
    solve()
