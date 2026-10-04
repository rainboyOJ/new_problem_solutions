#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 10:53
# update_at: 2026-10-01 10:53

import sys


def find(belong: list[int], x: int) -> int:
    """返回 x 所在染色块的块根：块内最靠近根节点、也是最早被染色的那个点。"""
    while belong[x] != x:
        belong[x] = belong[belong[x]]  # 路径压缩：块只会向上合并，深度不会变深
        x = belong[x]
    return x


def min_cost(weight: list[int], father: list[int], n: int, root: int) -> int:
    """贪心合并染色块：每次把平均值最大的非根块并进父块，累加跨块代价。"""
    belong = list(range(n + 1))  # 并查集；根节点所在块始终以 root 为块根
    up = father[:]               # up[x]：点 x 的父节点落在哪个块里
    up[root] = root              # 根块之上没有块，指向自己表示"无父块"
    size = [1] * (n + 1)         # size[x]：块根 x 这一块的点数
    total = weight[:]            # total[x]：块根 x 这一块的权值和

    cost = sum(weight)  # 每个点自己那一轮先把 A[i] 记一次
    for _ in range(n - 1):
        # 除根块外平均值最大的块，一定整体紧跟在父块之后染色才最优
        blocks = [x for x in range(1, n + 1) if belong[x] == x and x != root]
        best = max(blocks, key=lambda x: total[x] / size[x])
        parent_block = find(belong, up[best])
        # best 块每个点都排在父块每个点之后，这一批"后来者"各产生一次代价
        cost += total[best] * size[parent_block]
        up[best] = parent_block
        belong[best] = parent_block  # best 并入父块，不再是块根
        size[parent_block] += size[best]
        total[parent_block] += total[best]

    return cost


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, root = next(data), next(data)
    weight = [0] + [next(data) for _ in range(n)]  # 下标 1..n 对齐点编号
    father = [0] * (n + 1)
    for _ in range(n - 1):
        a, b = next(data), next(data)
        father[b] = a  # 题面给的每对是（父节点，子节点）
    print(min_cost(weight, father, n, root))


if __name__ == "__main__":
    solve()
