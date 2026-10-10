#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:18
# update_at: 2026-10-08 02:18

import sys
from collections import defaultdict

type Adj = list[list[int]]                    # 邻接矩阵，1 表示有边
type Dp = list[defaultdict[int, int]]         # dp[点集][叶子集] = 树的棵数


def lowbit_index(mask: int) -> int:
    """最低位 1 的下标（0-based），即「编号最小的元素」。"""
    return (mask & -mask).bit_length() - 1


def count_death_trees(n: int, adj: Adj, leaves: int) -> int:
    """统计恰含 leaves 个叶子的带标号生成树棵数。

    dp[mask][leaf] = 点集 mask、叶子集恰为 leaf 的树棵数。
    去重靠一条唯一性：规定每次剥离「当前树中编号最小的叶子」j = lowbit(leaf)，
    j 在树中的唯一邻居 k 必不是叶子（k ∉ leaf），剥掉 j 后叶子集只会
    「不变」（k 原非叶子）或「多出 k」（k 原为叶子），故递推唯一、无重无漏。
    """
    full = (1 << n) - 1
    dp: Dp = [defaultdict(int) for _ in range(full + 1)]

    for mask in range(1, full + 1):
        if bin(mask).count("1") == 2:
            # base：恰一条边，两点都是叶子
            x = lowbit_index(mask)
            y = lowbit_index(mask ^ (1 << x))
            if adj[x][y]:
                dp[mask][mask] = 1
            continue

        leaf = mask
        while leaf:                                    # 枚举 mask 的所有子集当叶子集
            j = lowbit_index(leaf)                     # 最后被剥离的点
            rest, old = mask ^ (1 << j), leaf ^ (1 << j)
            for k in range(n):
                kb = 1 << k
                # k 是 j 在旧树里的唯一邻居：在 mask 内、不是叶子、且与 j 有边
                k_can_be_parent = mask & kb and not leaf & kb and adj[j][k]
                if k_can_be_parent:
                    dp[mask][leaf] += dp[rest][old] + dp[rest][old | kb]
            leaf = (leaf - 1) & mask

    return sum(cnt for leaf, cnt in dp[full].items() if bin(leaf).count("1") == leaves)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, leaf_count = next(data), next(data), next(data)

    adj: Adj = [[0] * n for _ in range(n)]
    for _ in range(m):
        a, b = next(data) - 1, next(data) - 1
        adj[a][b] = adj[b][a] = 1

    print(count_death_trees(n, adj, leaf_count))


if __name__ == "__main__":
    solve()
