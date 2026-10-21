#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:40
# update_at: 2026-10-21 09:10
#
# main.py：跳楼机。从 1 楼出发，每次可向上跳 x/y/z 层，统计不超过 h 的可达楼层数。
# h 可达 2^63-1，逐层标记不可行；但三个步长都 <= 1e5，所以该压缩的维度是"楼层"。
# 取最小步长 base，把所有楼层按模 base 的余数分成 base 个等价类（商集 Z/baseZ）。
# 同一类里一旦能到 L，则 L+base、L+2base 也都能到——前提是 base 本身是合法步长。
# 所以每类只需知道最早可达楼层 dist[r]，其余全部由「加 base」生成。
# 把一步 s 作用到余数上是平移 r -> (r+s) mod base，它在 Z_base 里封闭，
# 于是整张图就是循环群关于生成集 {x mod base, y mod base, z mod base} 的 Cayley 图：
# 点 base 个、每点 3 条出边，与 h 的规模完全无关。在此基础上跑 Dijkstra 求 dist。
# 最后每类贡献 floor((h-dist[r])/base)+1 层；同余分类是划分，按类求和不会重复。

import sys
from heapq import heappop, heappush

INF = 1 << 62  # 整数哨兵；Python int 任意精度，不必担心 h + step 溢出


def earliest_reachable(height: int, steps: list[int]) -> list[int]:
    """返回 dist：dist[r] 为「模 base 余 r」这一类里的最早可达楼层。

    base 取 min(steps)：它必须是合法步长（否则「加 base 仍可达」不成立），
    取最小只是为了让余数图最小。
    """
    base = min(steps)

    dist = [INF] * base
    start = 1 % base
    dist[start] = 1  # 起点是 1 楼，不是 0

    heap: list[tuple[int, int]] = [(1, start)]  # (楼层, 余数)，楼层在前才能按它比大小

    while heap:
        current, residue = heappop(heap)
        if current != dist[residue]:
            continue  # 堆里的过期记录

        for step in steps:
            next_residue = (residue + step) % base
            candidate = current + step
            if candidate < dist[next_residue]:
                dist[next_residue] = candidate
                heappush(heap, (candidate, next_residue))

    return dist


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    height = next(data)
    steps = [next(data), next(data), next(data)]

    dist = earliest_reachable(height, steps)
    base = min(steps)

    # 每个余数类独立贡献：最早可达楼层之后，每加一次 base 仍可达。
    # 必须过滤 dist > height，否则 (height - dist) 为负会多算。
    print(sum((height - value) // base + 1 for value in dist if value <= height))


if __name__ == "__main__":
    solve()
