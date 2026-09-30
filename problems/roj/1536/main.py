#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:55
# update_at: 2026-09-30 16:55

import sys

MAX_X = 32001  # x 坐标最大为 32000，转为 1-based 下标最大 32001


def add(tree: list[int], idx: int, delta: int) -> None:
    """在树状数组 idx 位置增加 delta。"""
    while idx < len(tree):
        tree[idx] += delta
        idx += idx & -idx


def query(tree: list[int], idx: int) -> int:
    """查询树状数组前缀和 [1, idx]。"""
    res = 0
    while idx > 0:
        res += tree[idx]
        idx -= idx & -idx
    return res


def count_star_levels(n: int, coords: list[tuple[int, int]]) -> list[int]:
    """按给出顺序依次统计每颗星星的等级分布。"""
    tree = [0] * (MAX_X + 1)
    level_counts = [0] * n
    for x, _ in coords:
        pos = x + 1  # 树状数组下标从 1 开始
        level = query(tree, pos)
        level_counts[level] += 1
        add(tree, pos, 1)
    return level_counts


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    coords = [(next(data), next(data)) for _ in range(n)]
    ans = count_star_levels(n, coords)
    print("\n".join(map(str, ans)))


if __name__ == "__main__":
    solve()
