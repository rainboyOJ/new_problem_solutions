#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:19
# update_at: 2026-10-08 06:19

import sys
from collections import deque
from functools import reduce
from operator import xor

type Adj = list[list[tuple[int, int]]]  # adj[x] = [(终点 y, 颜色 c), ...]，同色多条边各占一项
type Preds = list[list[int]]            # preds[y] = [所有出边指向 y 的起点 x]


def grundy(n: int, adj: Adj, preds: Preds) -> list[int]:
    """算出每个点单独摆一颗石子时的 SG 值：逆拓扑序递推，SG(x) = mex(span{h_c})。"""
    rest = [len(adj[x]) for x in range(n + 1)]  # 剩余出度，逆拓扑 Kahn 的出队条件
    sg = [0] * (n + 1)                          # 出度为 0 的点无操作，SG 恒为 0
    que = deque(x for x in range(1, n + 1) if not rest[x])
    while que:
        x = que.popleft()
        if adj[x]:                              # 有出边才需要求 SG
            color_xor = {}                      # 颜色 c -> 该色所有出边终点 SG 的异或和
            for y, c in adj[x]:
                color_xor[c] = color_xor.get(c, 0) ^ sg[y]
            basis = {}                          # 主元所在位 -> 基向量，span{h_c} 的线性基
            for v in color_xor.values():
                b = v.bit_length() - 1
                while b >= 0 and b in basis:
                    v ^= basis[b]               # 消去最高位后继续找主元
                    b = v.bit_length() - 1
                if b >= 0:
                    basis[b] = v
            j = 0                               # mex(span) = 2^(最小的非主元位)，SG 恒为 2 的幂
            while j in basis:
                j += 1
            sg[x] = 1 << j
        for y in preds[x]:                      # x 的 SG 已定，回报给所有前驱
            rest[y] -= 1
            if not rest[y]:
                que.append(y)
    return sg


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: Adj = [[] for _ in range(n + 1)]
    preds: Preds = [[] for _ in range(n + 1)]
    for _ in range(m):
        s, t, c = next(data), next(data), next(data)
        adj[s].append((t, c))
        preds[t].append(s)

    sg = grundy(n, adj, preds)
    q = next(data)
    stones = [next(data) for _ in range(q)]
    total = reduce(xor, (sg[pos] for pos in stones), 0)  # 局面 SG = 各颗石子 SG 的异或和
    print(1 if total else 0)


if __name__ == "__main__":
    solve()
