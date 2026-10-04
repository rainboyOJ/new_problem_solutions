#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 00:58
# update_at: 2026-10-01 00:58

import sys
from functools import reduce
from operator import xor


def sg_table(max_stones: int, moves: list[int]) -> list[int]:
    """算出 0..max_stones 每堆石子的 SG 值：SG(x) 是 x 走一步能到的 SG 里最小的缺失值。"""
    n = max(max_stones + 2, len(moves) + 2)  # SG 值不会超过取法种数，但下标要留够余量
    stamp = [0] * n                          # stamp[v] == x 表示 v 被 x 这一轮占用
    sg = [0] * (max_stones + 1)
    for x in range(1, max_stones + 1):
        for take in moves:
            if take > x:
                break                        # moves 递增，后面的取法都取不动了
            stamp[sg[x - take]] = x          # 拿 x 当时间戳，省掉每轮清零
        while stamp[sg[x]] == x:             # 本轮的 SG 集合里最小的缺失值就是 mex
            sg[x] += 1
    return sg


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    heaps = [next(data) for _ in range(n)]
    m = next(data)
    moves = sorted(next(data) for _ in range(m))  # 题面保证递增，这里排序只为不依赖该保证

    sg = sg_table(max(heaps), moves)
    nim = reduce(xor, map(sg.__getitem__, heaps), 0)  # 游戏是 N 堆独立子游戏，整体 SG 就是异或和

    # 一步后要让整体异或和变成 0：第 i 堆必须从 sg[a] 落到 nim ^ sg[a]
    first = next(
        (
            (i + 1, take)
            for i, a in enumerate(heaps)
            for take in moves
            if take <= a and sg[a - take] == nim ^ sg[a]
        ),
        None,
    )

    if first is None:
        print("NO")
    else:
        print("YES")
        print(*first)


if __name__ == "__main__":
    solve()
