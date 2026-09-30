#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:20
# update_at: 2026-09-30 16:20

import sys

POSSIBLE = "Ordering is possible."
IMPOSSIBLE = "The door cannot be opened."


def find(root: list[int], x: int) -> int:
    """并查集查根（路径折半压缩），用来判断字母是否落在同一连通分量。"""
    while root[x] != x:
        root[x] = root[root[x]]
        x = root[x]
    return x


def can_order(edges: list[tuple[int, int]]) -> bool:
    """所有单词能否首尾相接排成一列：有向图欧拉路径判定。

    每条边 (u, v) 表示"末字母 v 接在首字母 u 后面"。判定条件：
    非零度点弱连通，且入度之差只允许 0 或至多一对 +1/-1。
    """
    ind = [0] * 26
    outd = [0] * 26
    root = list(range(26))
    for u, v in edges:
        outd[u] += 1
        ind[v] += 1
        root[find(root, u)] = find(root, v)  # 无向意义下并起来，连通性靠它判
    used = [i for i in range(26) if ind[i] or outd[i]]
    if len({find(root, i) for i in used}) > 1:  # 非零度点必须同属一个分量
        return False
    # 欧拉路径：起点出-入=1、终点入-出=1，其余点入=出；守恒保证 +1 与 -1 成对
    gap = [outd[i] - ind[i] for i in used]
    return all(abs(g) <= 1 for g in gap) and gap.count(1) <= 1 and gap.count(-1) <= 1


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    T = int(next(it))
    out: list[str] = []

    for _ in range(T):
        N = int(next(it))
        edges: list[tuple[int, int]] = []
        for _ in range(N):
            word = next(it)  # 整个单词只为取首末字母（小写字母 → 下标 = ASCII-97）
            edges.append((word[0] - 97, word[-1] - 97))
        out.append(POSSIBLE if can_order(edges) else IMPOSSIBLE)

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
