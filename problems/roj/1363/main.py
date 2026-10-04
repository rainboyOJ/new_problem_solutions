#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 07:16
# update_at: 2026-09-30 07:16

import sys


def leaf_of(depth: int, index: int) -> int:
    """第 index 个小球停下的叶子序号：每层用 index 的奇偶定方向，再把 index 折半。"""
    node = 1
    for _ in range(depth - 1):
        go_left = index & 1  # 该节点第奇数次被访问 → 走左，偶数次 → 走右
        node = 2 * node + (1 - go_left)
        index = (index + go_left) >> 1  # 走左的球挤进前一半，走右的球落到后一半
    return node


def solve() -> None:
    depth, index = map(int, sys.stdin.buffer.read().split())
    print(leaf_of(depth, index))


if __name__ == "__main__":
    solve()
