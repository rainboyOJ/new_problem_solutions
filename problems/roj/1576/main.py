#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 19:30
# update_at: 2026-09-30 19:30

import sys
from functools import cache

NEG = -10**9  # 不可达的选课方案（学分总和至多 100×20 = 2000）

CHILDREN: list[list[int]] = []  # 邻接表，下标 0 兼作"虚拟根"
CREDIT: list[int] = []          # 学分表，CREDIT[0] = 0


def pack(sub: list[int], add: list[int], cap: int) -> list[int]:
    """合并两张方案表：total[a+b] = max(sub[a] + add[b])，总门数不超过 cap。"""
    total = [NEG] * (cap + 1)
    for a, x in enumerate(sub):
        if x == NEG:
            continue
        for b, y in enumerate(add):
            if y != NEG and a + b <= cap:
                total[a + b] = max(total[a + b], x + y)
    return total


@cache
def dfs(u: int, cap: int) -> list[int]:
    """子树 u 的方案表 best[k]：选 k 门课的最高学分；k=0 表示一门不选，选课必含 u。"""
    best = [NEG] * (cap + 1)
    # 初始只含 u 自己：先修课没选就一门都不能选，故 u 的 best[0] 先置为不可达
    best[1 if u else 0] = CREDIT[u] if u else 0  # 虚拟根 0 不占课程名额
    for v in CHILDREN[u]:  # 逐个孩子并入：选了父节点才有资格选孩子
        best = pack(best, dfs(v, cap), cap)
    best[0] = 0  # 一门不选恒合法，供父节点表示"跳过该子树"
    return best


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    global CHILDREN, CREDIT
    M, N = next(data), next(data)  # 待选课程数 / 可选课程数

    CHILDREN = [[] for _ in range(M + 1)]  # 先修为 0 的课挂在虚拟根 0 下
    CREDIT = [0]
    for u in range(1, M + 1):
        pre, cr = next(data), next(data)
        CREDIT.append(cr)
        CHILDREN[pre].append(u)

    print(dfs(0, N)[N])  # 虚拟根方案表第 N 项 = 恰好选 N 门课的最高学分


if __name__ == "__main__":
    solve()
