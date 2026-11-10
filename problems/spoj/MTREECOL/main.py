#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-10 12:15
# update_at: 2026-11-10 12:15

import sys


def solve_case(n: int, root: int, w: list[int], edges: list[tuple[int, int]]) -> int:
    """求树上染色的最小代价（平均权值贪心 + 贡献法延后增量）。"""
    fa = [0] * (n + 1)
    for u, v in edges:
        fa[v] = u

    p = list(range(n + 1))

    def find(x: int) -> int:
        if p[x] != x:
            p[x] = find(p[x])
        return p[x]

    weight = [0] + w
    siz = [1] * (n + 1)
    ans = sum(w)

    for _ in range(n - 1):
        # 挑选平均值最大的非根代表元
        best_u = -1
        for i in range(1, n + 1):
            if i == root or find(i) != i:
                continue
            if best_u == -1 or weight[i] * siz[best_u] > weight[best_u] * siz[i]:
                best_u = i

        f = find(fa[best_u])
        ans += siz[f] * weight[best_u]

        # 并查集合并
        p[best_u] = f
        siz[f] += siz[best_u]
        weight[f] += weight[best_u]

    return ans


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []

    while True:
        token = next(data, None)
        if token is None:
            break
        n = int(token)
        root = int(next(data))
        if n == 0 and root == 0:
            break

        w = [int(next(data)) for _ in range(n)]
        edges = [(int(next(data)), int(next(data))) for _ in range(n - 1)]

        out.append(str(solve_case(n, root, w, edges)))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
