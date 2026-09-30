#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 08:10
# update_at: 2026-09-30 08:10

import sys


def transitive_closure(adj: list[int]) -> list[int]:
    """bitset 版 Floyd 传递闭包：reach[i] = i 能到达的点集（含自己）的位掩码。"""
    reach = adj[:]
    for k in range(len(reach)):
        rk = reach[k]
        # i 能到 k，就能到 k 能到的一切：一次大整数 OR 完成整行转移
        reach = [r | rk if r >> k & 1 else r for r in reach]
    return reach


def count_source_sccs(reach: list[int], pred: list[int]) -> int:
    """统计"源"强连通分量个数：能到 i 的点都能被 i 反向到达，说明没有外部边进入 i 所在分量。"""
    return len({reach[i] & pred[i] for i in range(len(reach)) if not pred[i] & ~reach[i]})


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    adj: list[int] = []
    for i in range(n):
        bits = 1 << i  # 自己算进可达集，闭包与 SCC 判断都依赖这一点
        while j := next(data):  # 每行以 0 结尾
            bits |= 1 << (j - 1)
        adj.append(bits)

    reach = transitive_closure(adj)
    pred = [sum(1 << j for j in range(n) if reach[j] >> i & 1) for i in range(n)]  # reach 的第 i 列
    print(count_source_sccs(reach, pred))


if __name__ == "__main__":
    solve()
