#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 00:00
# update_at: 2026-10-21 00:00

import sys


class Dsu:
    """并查集：路径压缩 + 按大小合并，对应 C++ 版的 dsu_find / dsu_merge。"""

    def __init__(self, n: int) -> None:
        self.parent = list(range(n + 1))  # parent[x]：x 的父节点，x 是根时等于 x
        self.size = [1] * (n + 1)         # size[x]：x 当根时所在集合的大小

    def find(self, x: int) -> int:
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]  # 路径减半
            x = self.parent[x]
        return x

    def merge(self, a: int, b: int) -> bool:
        """合并 a、b 所在集合；两端已连通（这条边成环）返回 False。"""
        root_a, root_b = self.find(a), self.find(b)
        if root_a == root_b:
            return False
        if self.size[root_a] < self.size[root_b]:  # 小的接到大的下面
            root_a, root_b = root_b, root_a
        self.parent[root_b] = root_a
        self.size[root_a] += self.size[root_b]
        return True


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m, k = next(data), next(data), next(data)

    # edges[i]：第 i 条道路 (u, v)，c = 0 鹅卵石路，c = 1 水泥路
    edges = [(next(data), next(data), next(data)) for _ in range(m)]

    # ---------- 第一遍 Kruskal：先加全部水泥路，再补鹅卵石路 ----------
    # 求出"任何生成树至少需要"的鹅卵石路条数 need，
    # 同时标记桥接水泥连通块的"不得不选"鹅卵石路 forced。
    dsu = Dsu(n)
    cement_cnt = sum(dsu.merge(u, v) for u, v, c in edges if c == 1)
    forced = [False] * (m + 1)
    need = 0
    for i, (u, v, c) in enumerate(edges, 1):
        if c == 0 and dsu.merge(u, v):
            forced[i] = True
            need += 1

    # 图不连通，或最少的鹅卵石路都超过 k，都无解。
    if cement_cnt + need != n - 1 or need > k:
        print("no solution")
        return

    # ---------- 第二遍 Kruskal：精确凑够 k 条鹅卵石路 ----------
    # 先放回 forced 的鹅卵石路，再挑其余鹅卵石路补到 k 条，最后水泥路填满。
    dsu = Dsu(n)
    plan: list[int] = []  # 方案的边编号，恰好 n - 1 条
    for i, (u, v, c) in enumerate(edges, 1):
        if forced[i]:
            dsu.merge(u, v)  # forced 是森林，必定合并成功
            plan.append(i)
    cobble_cnt = len(plan)
    for i, (u, v, c) in enumerate(edges, 1):
        if cobble_cnt >= k:
            break
        if c == 0 and not forced[i] and dsu.merge(u, v):
            plan.append(i)
            cobble_cnt += 1
    if cobble_cnt < k:  # 凑不满 k 条：鹅卵石路在生成树里放不下这么多
        print("no solution")
        return
    for i, (u, v, c) in enumerate(edges, 1):
        if c == 1 and dsu.merge(u, v):
            plan.append(i)

    plan.sort()  # 按输入顺序输出，便于对照
    out = [f"{edges[i - 1][0]} {edges[i - 1][1]} {edges[i - 1][2]}" for i in plan]
    print("\n".join(out))


if __name__ == "__main__":
    solve()
