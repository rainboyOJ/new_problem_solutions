#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:45
# update_at: 2026-10-07 21:45

import sys
from bisect import bisect_left, bisect_right
from operator import mul

MOD = 1 << 32        # 评估值对 2^32 取模，也就是只留低 32 位
MASK = MOD - 1       # x & MASK 等价于 x mod 2^32
W = 7                # 每个多项式存 0..6 次共 7 个系数，K <= 6 够用

type Poly = tuple[list[int], list[int]]  # (前缀积多项式, 它的形式逆)：每 7 个数一段的平铺表；
                                         # 逆的每一段是「次数从高到低」存放，询问时一次切片即得卷积序
type Rmq = list[list[int]]               # 稀疏表：第 k 行是长度 2^k 的区间最小值，用于查 [l, r] 最小 V

FAC = [1, 1, 2, 6, 24, 120, 720]         # K!，K <= 6


def build_prefix(vals: list[int]) -> Poly:
    """扫一遍 V，产出每个前缀的段积多项式 P[m] = Π_{i<m}(1 + V_i·y) 及其形式逆。

    P[m+1] = P[m]·(1 + v·y) 的每一项都只用到低一次的旧值，所以 p 从高次往低次原地递推：
    p_k ← p_k + v·p_{k-1}；形式逆则从 P[m] = P[m+1]·(1 + v·y) 反解出
    q_k ← q_k - v·q_{k-1}，其中的 q_{k-1} 必须是刚更新过的那一个，所以 q 反而从低次往高次递推。
    两边都是每扫一个 V 做 O(K) 次乘法。
    """
    pref = [1, 0, 0, 0, 0, 0, 0]  # P[0] = 1
    invp = [0, 0, 0, 0, 0, 0, 1]  # P[0] 的逆还是 1，逆序存放后正好是 7 个数一段
    p, q = [1, 0, 0, 0, 0, 0, 0], [1, 0, 0, 0, 0, 0, 0]
    for v in vals:
        for k in range(W - 1, 0, -1):  # 从高次往低次：p[k-1] 这一轮还没被新的覆盖
            p[k] = (p[k] + v * p[k - 1]) & MASK
        for k in range(1, W):          # 反解要的是新 q[k-1]，所以从低次往高次
            q[k] = (q[k] - v * q[k - 1]) & MASK
        pref += p
        invp += q[::-1]
    return pref, invp


def build_rmq(vals: list[int]) -> Rmq:
    """区间最小值稀疏表：第 k 行的第 i 项是 [i, i+2^k) 的最小值。"""
    rmq = [vals]
    span = 1
    while span * 2 <= len(vals):
        prev = rmq[-1]
        rmq.append(list(map(min, prev, prev[span:])))  # 两段相邻的 2^k 段拼出长度 2^{k+1}
        span *= 2
    return rmq


def plan_value(poly: Poly, rmq: Rmq, l: int, r: int, k: int) -> int:
    """区域下标限定在 [l, r]、选取 k 块时，这一项计划的评估值（mod 2^32）。

    评估值 = k! × (去掉 V 最小那块后的 k 次初等对称和)，而「去掉最小块」等于乘上
    (1 + min_v·y) 的形式逆 1 - min_v·y + min_v²·y² - …，所以只用一次区间最小值和
    [l, r] 多项式的前 k+1 个系数。
    """
    if r - l + 1 <= k:  # 还得先排除最小的一块，所以至少要 k+1 块区域；空区间也走这里
        return 0

    width = (r - l + 1).bit_length() - 1      # 两块长度 2^width 的区间盖住 [l, r]
    minv = min(rmq[width][l], rmq[width][r - (1 << width) + 1])

    pref, invp = poly
    tail = pref[(r + 1) * W:(r + 1) * W + W]  # [0, r+1) 的前缀积多项式
    head = invp[l * W:(l + 1) * W]            # [0, l) 前缀积的形式逆（Poly 约定的逆序块）
    # [l, r] 多项式 = 前缀积 · (左端前缀积)^{-1}，第 j 个系数就是 j 次初等对称和；
    # head 是逆序块，所以第 j 个系数的点积要用 head 的尾段挨着 tail 的头段
    coef = [1] + [
        sum(map(mul, tail[:j + 1], head[W - 1 - j:])) & MASK for j in range(1, k + 1)
    ]

    acc, pw = 0, 1                            # pw 是 (-min_v)^j
    for j in range(k + 1):
        acc = (acc + pw * (1 if j == k else coef[k - j])) & MASK
        pw = pw * (MOD - minv) & MASK
    return acc * FAC[k] & MASK


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, q = next(data), next(data)

    ds = [next(data) for _ in range(n)]       # 每块区域的 D
    vs = [next(data) for _ in range(n)]       # 每块区域的 V
    order = sorted(range(n), key=ds.__getitem__)  # 按 D 升序，D 的区间就变成下标区间
    ds = [ds[i] for i in order]
    vs = [vs[i] for i in order]

    poly = build_prefix(vs)
    rmq = build_rmq(vs)

    out: list[str] = []
    for _ in range(q):
        L, R, k = next(data), next(data), next(data)
        l = bisect_left(ds, L)                # 第一个 D >= L 的位置
        r = bisect_right(ds, R) - 1           # 最后一个 D <= R 的位置
        out.append(str(plan_value(poly, rmq, l, r, k)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
