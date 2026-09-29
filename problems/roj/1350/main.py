#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 20:30
# update_at: 2026-10-08 20:30

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    g = [[next(data) for _ in range(n)] for _ in range(n)]  # n*n 距离矩阵

    INF = float('inf')
    dis = g[0][:]        # dis[j]：树外点 j 到当前树的最短边长，初始树只有农场 0
    dis[0] = INF         # 农场 0 已在树里，不参与选取
    in_tree = [True] + [False] * (n - 1)  # 点是否已并入生成树
    answer = 0
    for _ in range(n - 1):  # 每轮并入一个点、加一条边，共 n-1 轮
        k = min(range(n), key=dis.__getitem__)  # 距离树最近的树外点 k
        answer += dis[k]
        in_tree[k] = True
        # 用 k 的出边松弛：树外的点取 min，树内的点一律置回 INF 不再参与
        dis = [INF if t else min(d, gk) for d, gk, t in zip(dis, g[k], in_tree)]

    print(answer)


if __name__ == "__main__":
    solve()
