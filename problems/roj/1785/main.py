#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 03:20
# update_at: 2026-10-08 03:35

import sys

# 题面【题目描述】的 "x = x/2" 是排版笔误：三个官方样例只有 x = x*2 能同时对上
# （1 1 50 -> 1.0；5 3 0 -> 3.0；5 3 25 -> 1.921875 = 123/64），本解按 x = x*2 实现。
B = 10            # 低 B 位精确记录；n <= 200 时 B >= 8 就够，取 10 兼顾余量与速度
SZ = 1 << B       # 低 B 位的取值个数
MASK = SZ - 1     # 低 B 位全 1，用于判断"低 B 位是否全是 1"

type Prob = list[float]                # 某个 t 下按 s 索引的概率数组
type Bucket = list[tuple[Prob, Prob]]  # bucket[t] = (概率数组 P, 游程期望贡献数组 Q)


def step_state(s: int, t: int, pr: float, qk: float, dst: Bucket, add1: float, mul2: float) -> None:
    """把状态 (s,t) 的概率 pr 与游程期望贡献 qk 按两种操作推到本轮的新数组上。"""
    if add1:  # w += 1
        if s != MASK:
            dp, dq = dst[t]
            dp[s + 1] += pr * add1
            dq[s + 1] += qk * add1
        else:  # 低 B 位归零、进位进入第 B 位，该位取反
            dp, dq = dst[t ^ 1]
            dp[0] += pr * add1
            # t=1 时进位穿过整段 1，游程原样变成 k 个 0（k 不变）；t=0 时重置为 1
            dq[0] += (qk if t else pr) * add1
    if mul2:  # w *= 2
        bit = s >> (B - 1)  # 左移后进入第 B 位的那一位，它就是新的 t
        dp, dq = dst[bit]
        ns = (s << 1) & MASK
        gain = qk + pr if bit == t else pr  # 该位等于 t 则游程 k+1，否则重置为 1
        dp[ns] += pr * mul2
        dq[ns] += gain * mul2


def expectation(x: int, n: int, p: int) -> float:
    """算 n 次操作后 v2(w) 的期望（v2 即二进制末尾 0 的个数）。

    状态 = (s, t, k)：s = w mod 2^B 精确记录，t = w 的第 B 位，
    k = 从第 B 位起连续等于 t 的位数。于是 v2(w) 可读出：s != 0 时是 v2(s)，
    s = 0 且 t = 1 时是 B，s = 0 且 t = 0 时是 B + k。
    三种转移对 k 都是仿射的（k' = k、k+1 或常数 1），所以每个 (s,t) 只存两个量：
    P = Σ_k Pr[s][t][k] 与 Q = Σ_k k·Pr[s][t][k]，答案里 B + k 那一支聚合后就是 B·P + Q。
    """
    add1 = 1.0 - p / 100.0  # w += 1 的概率
    mul2 = p / 100.0        # w *= 2 的概率

    p0, q0 = [0.0] * SZ, [0.0] * SZ  # t = 0：第 B 位是 0
    p1, q1 = [0.0] * SZ, [0.0] * SZ  # t = 1：第 B 位是 1

    # 初值：低 B 位取 x；t0 是 x 的第 B 位；k0 是 x >> B 从最低位起连续等于 t0 的位数
    s0 = x & MASK
    hi = x >> B
    t0 = hi & 1
    k0 = 0
    while hi >> k0 and (hi >> k0 & 1) == t0:
        k0 += 1
    k0 = max(k0, 1)  # x < 2^B 时高位全是 0，按"第 B 位起是 1 个 0"记
    (p1 if t0 else p0)[s0] = 1.0
    (q1 if t0 else q0)[s0] = k0

    for _ in range(n):
        np0, nq0 = [0.0] * SZ, [0.0] * SZ
        np1, nq1 = [0.0] * SZ, [0.0] * SZ
        dst: Bucket = [(np0, nq0), (np1, nq1)]
        for s in range(SZ):
            if p0[s]:
                step_state(s, 0, p0[s], q0[s], dst, add1, mul2)
            if p1[s]:
                step_state(s, 1, p1[s], q1[s], dst, add1, mul2)
        p0, q0, p1, q1 = np0, nq0, np1, nq1

    # (s & -s).bit_length() - 1 就是 v2(s)（s >= 1）；s = 0 的两支是 B 与 B + k
    ans = sum(((s & -s).bit_length() - 1) * (p0[s] + p1[s]) for s in range(1, SZ))
    return ans + B * (p0[0] + p1[0]) + q0[0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    x, n, p = next(data), next(data), next(data)
    print(f"{expectation(x, n, p):.10f}")


if __name__ == "__main__":
    solve()
