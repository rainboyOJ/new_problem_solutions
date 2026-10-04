#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:11
# update_at: 2026-10-02 12:30

import sys
from itertools import accumulate


def read_input() -> tuple[int, list[int], list[int]]:
    """读入全部数据：返回 (n, cnt[v] = 魔法值 v 的物品个数, 每个物品的魔法值)。"""
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)
    items = [next(data) for _ in range(m)]
    cnt = [0] * (n + 1)
    for v in items:
        cnt[v] += 1
    return n, cnt, items


def solve() -> None:
    n, cnt, items = read_input()

    # ans_r[v]：值为 v 的某一个物品作为角色 r 出现的魔法阵个数（按值统计，最后按物品查表）
    ans_a = [0] * (n + 1)
    ans_b = [0] * (n + 1)
    ans_c = [0] * (n + 1)
    ans_d = [0] * (n + 1)

    # 枚举 t = Xb - Xa = 2(Xd - Xc)，必须是偶数；u = t/2 = Xd - Xc。
    # 固定 t 后：A=a、B=a+t；由 Xb-Xa < (Xc-Xb)/3 得 C ≥ B+3t+1 = a+4t+1；D = C+u ≤ n。
    # a 的可行上界 am = n - u - 4t - 1（保证 C 的最小值 a+4t+1 与 D 的偏移 u 不越过 n）。
    t = 2
    while n - t // 2 - 4 * t - 1 >= 1:
        u = t // 2
        am = n - u - 4 * t - 1

        # AB 侧权重 p[a] = cnt[a]*cnt[a+t]：A、B 各自选物品的组合数；pre[x] = p[1..x] 的和
        p = [cnt[a] * cnt[a + t] for a in range(1, am + 1)]
        pre = list(accumulate(p, initial=0))

        # CD 侧权重 w[c] = cnt[c]*cnt[c+u]：C 取 c、D 取 c+u 的组合数，c ∈ [4t+2, n-u]；
        # suf[k] = w 的最后 k 项之和，于是 W(a) = Σ_{c≥a+4t+1} w[c] = suf[am+1-a]
        w = [cnt[c] * cnt[c + u] for c in range(4 * t + 2, n - u + 1)]
        suf = list(accumulate(reversed(w), initial=0))
        wsum = suf[am:0:-1]  # wsum[a-1] = W(a)，a = 1..am

        # A/B 角色：固定该物品后，另一侧选物品数 × CD 侧权重和
        ans_a[1:am + 1] = [x + cb * s for x, cb, s in zip(ans_a[1:am + 1], cnt[t + 1:], wsum)]
        ans_b[t + 1:t + am + 1] = [x + ca * s for x, ca, s in zip(ans_b[t + 1:t + am + 1], cnt[1:am + 1], wsum)]

        # C/D 角色：c 从 4t+2 到 n-u，P = pre[c-4t-1] = Σ_{a≤c-4t-1} p[a]；D = c+u
        pc = pre[1:]
        ans_c[4 * t + 2:n - u + 1] = [x + cd * q for x, cd, q in zip(ans_c[4 * t + 2:n - u + 1], cnt[4 * t + 2 + u:], pc)]
        ans_d[4 * t + 2 + u:n + 1] = [x + c0 * q for x, c0, q in zip(ans_d[4 * t + 2 + u:n + 1], cnt[4 * t + 2:n - u + 1], pc)]

        t += 2

    print("\n".join(f"{ans_a[v]} {ans_b[v]} {ans_c[v]} {ans_d[v]}" for v in items))


if __name__ == "__main__":
    solve()
