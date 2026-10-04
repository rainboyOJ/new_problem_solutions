#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:50
# update_at: 2026-10-02 09:05

import sys

V_BITS = 20  # 顶点编号占 20 位：N ≤ 20000 < 2^20，怨气值放在高 40 位
V_MASK = (1 << V_BITS) - 1

FA: list[int] = []   # 并查集父节点，下标 0 不用
REL: list[int] = []  # 节点与父节点的仇敌关系：0 同监狱，1 不同监狱


def find(x: int) -> int:
    """找根并路径压缩；返回时 REL[x] 更新为 x 与根的仇敌关系（0 同监，1 异监）。"""
    path: list[int] = []
    while FA[x] != x:
        path.append(x)
        x = FA[x]
    # 从根往回累计异或：每个节点只读一次自己的旧关系，读完立即改挂到根
    acc = 0
    for node in reversed(path):
        acc ^= REL[node]
        REL[node] = acc
        FA[node] = x
    return x


def worst_conflict(edges: list[int]) -> int:
    """按怨气值从大到小加“异监”约束，返回第一条被迫同监的怨气值；全程无冲突为 0。"""
    for e in edges:
        b = e & V_MASK
        a = e >> V_BITS & V_MASK
        c = e >> V_BITS * 2
        ra, rb = find(a), find(b)
        if ra == rb:
            # 两人已被约束串起来：仇敌关系为 0 才会真的关进同一监狱
            if REL[a] ^ REL[b] == 0:
                return c
        else:
            # 合并两棵约束树，强制 a、b 分属两监：REL[ra] 取值让异或结果为 1
            FA[ra] = rb
            REL[ra] = REL[a] ^ REL[b] ^ 1
    return 0


def solve() -> None:
    # 逐行惰性切分：不一次性生成几十万个 token 字符串，给 32MB 内存限制让路
    data = (int(tok) for line in sys.stdin.buffer for tok in line.split())
    n, m = next(data), next(data)

    edges: list[int] = []
    for _ in range(m):
        a, b, c = next(data), next(data), next(data)
        # 打包成一个整数再排序：高位 c 优先，降序等价于按怨气值降序，且省内存
        edges.append((c << V_BITS * 2) | (a << V_BITS) | b)
    edges.sort(reverse=True)

    FA[:] = list(range(n + 1))  # 并查集初始化
    REL[:] = [0] * (n + 1)

    print(worst_conflict(edges))


if __name__ == "__main__":
    solve()
