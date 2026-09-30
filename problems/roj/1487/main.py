#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47
import math
import sys


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    n, k = int(tokens[0]), int(tokens[1])
    pts = [(int(tokens[2 + 2 * i]), int(tokens[3 + 2 * i])) for i in range(n)]

    if k >= n:
        print("0.00")
        return

    # 生成所有点对的无向边并按欧氏距离升序排序
    edges = sorted(
        (math.hypot(pts[i][0] - pts[j][0], pts[i][1] - pts[j][1]), i, j)
        for i in range(n)
        for j in range(i + 1, n)
    )

    parent = list(range(n))

    def find(x: int) -> int:
        curr = x
        while parent[curr] != curr:
            curr = parent[curr]
        while parent[x] != curr:
            parent[x], x = curr, parent[x]
        return curr

    # Kruskal 算法求生成树，记录加入生成树的所有边权
    tree_weights: list[float] = []
    for w, u, v in edges:
        fu, fv = find(u), find(v)
        if fu != fv:
            parent[fu] = fv
            tree_weights.append(w)
            if len(tree_weights) == n - 1:
                break

    # k 台卫星设备可以使最多 k 个连通块各自内部连通或两两连通
    # 相当于消去生成树中权值最大的 max(k - 1, 0) 条边
    # 剩下的最大边权即为所求的无线电通讯距离 d
    remove_count = max(k - 1, 0)
    ans = tree_weights[-(remove_count + 1)] if remove_count < len(tree_weights) else 0.0
    print(f"{ans:.2f}")


if __name__ == "__main__":
    solve()
