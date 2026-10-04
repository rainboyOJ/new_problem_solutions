#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:01
# update_at: 2026-10-01 09:01

import sys
from array import array

BITS = 21  # 数值范围 0..2^21-1，从第 20 位往下逐位决策

CH = array("i", [0, 0])  # 01 字典树孩子表：节点 u 的 0/1 孩子存在 CH[2u]/CH[2u+1]，0 表示空
IDX = array("i", [-1])   # 节点值表：叶子记录该前缀值已插入的最大下标，非叶子恒为 -1


def insert(value: int, j: int) -> None:
    """把前缀值 value 插入 01 字典树，并在叶子登记下标 j。"""
    u = 0
    for k in range(BITS - 1, -1, -1):
        bit = value >> k & 1
        nxt = CH[2 * u + bit]
        if not nxt:                     # 该分支还没建，补一个叶子链节点
            nxt = len(IDX)
            CH.extend((0, 0))
            IDX.append(-1)
            CH[2 * u + bit] = nxt
        u = nxt
    # 同一个值后插入的下标更大，直接覆盖即保留"最大下标"→ 同值下子段最短
    IDX[u] = j


def query(value: int) -> int:
    """贪心走"异或后该位为 1"的分支，返回与 value 异出最大值的那个前缀下标。"""
    u = 0
    for k in range(BITS - 1, -1, -1):
        bit = value >> k & 1
        u = CH[2 * u + (bit ^ 1)] or CH[2 * u + bit]  # 对立位存在就走，保证该位异或为 1
    return IDX[u]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    # 前缀异或 b[0]=0 是"空前缀"哨兵：子段 [l,r] 的异或 = b[r] ^ b[l-1]
    b = [0] * (n + 1)
    for i in range(1, n + 1):
        b[i] = b[i - 1] ^ next(data)

    insert(0, 0)  # 哨兵空前缀：值 0、下标 0（对应起点 1）
    best_v, best_l, best_r = -1, 1, 1
    for r in range(1, n + 1):
        j = query(b[r])               # 只查 j < r，所以先查再插
        cand = b[r] ^ b[j]
        if cand > best_v:             # 严格大于：并列时先保留最早结尾，同结尾由叶子的最大下标保最短
            best_v, best_l, best_r = cand, j + 1, r
        insert(b[r], r)

    print(best_v, best_l, best_r)


if __name__ == "__main__":
    solve()
