#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 18:42
# update_at: 2026-10-07 18:42

import sys
from collections import deque

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Rev = list[list[int]]  # rev[u] = 会产生 u 号怪兽的那些怪兽编号


def settle(n: int, rev: Rev, dp: list[int], sump: list[int], pending: list[int]) -> None:
    """把"某只怪兽变便宜了"沿反向边不断推给会产生它的怪兽，直到没人还能变便宜。

    dp[i] = 彻底消灭一只 i 及其衍生怪的最小体力，初值取法术攻击 K_i；
    sump[i] = S_i + Σ dp[son] 是普通攻击路线的当前代价。
    谁出队就把攒下的下降量 d 交给父亲们，父亲重算后可能继续下降（怪兽可能变回自己，故有环）。
    """
    inq = bytearray(n + 1)  # inq[i]：i 是否已在队列里，避免重复入队
    q = deque()
    for i in range(1, n + 1):  # 一开始就"普通攻击更便宜"的怪兽先入队
        if sump[i] < dp[i]:
            pending[i] += dp[i] - sump[i]
            dp[i] = sump[i]
            inq[i] = 1
            q.append(i)

    while q:
        u = q.popleft()
        inq[u] = 0
        d = pending[u]
        pending[u] = 0
        if not d:
            continue
        for p in rev[u]:  # p 会产生 u，u 便宜了 p 的普通攻击也跟着便宜
            sump[p] -= d
            if sump[p] < dp[p]:
                pending[p] += dp[p] - sump[p]
                dp[p] = sump[p]
                if not inq[p]:
                    inq[p] = 1
                    q.append(p)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    s = [0] * (n + 1)  # s[i]：普通攻击 i 消耗的体力
    k = [0] * (n + 1)  # k[i]：法术攻击 i 消耗的体力
    rev: Rev = [[] for _ in range(n + 1)]
    for i in range(1, n + 1):
        s[i], k[i] = next(data), next(data)
        r = next(data)  # 题面的 R_i：i 死亡后产生的新怪兽个数
        for _ in range(r):
            rev[next(data)].append(i)  # 反过来记：父亲 i 会产生这个孩子

    sump = s[:]  # 普通攻击的 S_i 部分；Σ dp[son] 部分此时 dp 还是 K
    for u in range(1, n + 1):
        ku = k[u]
        for p in rev[u]:
            sump[p] += ku

    dp = k[:]  # 所有怪兽先假设用法术攻击，再让松弛把更便宜的方案找出来
    settle(n, rev, dp, sump, [0] * (n + 1))

    print(dp[1])  # 只有 1 号怪兽入侵村庄


if __name__ == "__main__":
    solve()
