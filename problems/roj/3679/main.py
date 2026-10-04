#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://roj.ac.cn  https://rbook.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 15:19
# update_at: 2026-10-02 15:19

import sys
from math import isqrt


def min_grow_days(a: int, b: int, c: int, D: int) -> int:
    """固定 D 天完成时，这棵树最少要连续生长几天（含种下当天）；返回值大于 D 表示做不到。

    第 x 天长高 max(b + x*c, 1)，连续生长 m 天（第 D-m+1 天种下）的总高度 S(m) 随 m 递增，
    这里直接解 S(m) >= a 的最小 m，避免对每个 D 再套一层二分。
    """
    if c == 0:
        return -(-a // b)  # 每天固定长 b 米，向上取整

    q = -c
    if c > 0 or (b - 1) // q >= D:
        # [1, D] 内每天生长量 b + x*c 都不小于 1：S(m) = (B*m - c*m*m)/2
        B = 2 * b + c * (2 * D + 1)
        if c > 0:
            delta = B * B - 8 * c * a
            if delta < 0:
                return D + 1  # 二次函数始终低于 a，从第 1 天种也长不到
            # 2S(m) >= 2a 即 c*m^2 - B*m + 2a <= 0，最小 m 是较小根向上取整
            m = (B - isqrt(delta) + 2 * c - 1) // (2 * c)  # 根的上界，再向下校准
            while m > 1 and B * (m - 1) - c * (m - 1) * (m - 1) >= 2 * a:
                m -= 1
            while m <= D and B * m - c * m * m < 2 * a:
                m += 1
            return m
        # c < 0 但整段都线性：q*m^2 + B*m >= 2a，取较大根向上取整
        m = max((isqrt(B * B + 8 * q * a) - B + 2 * q - 1) // (2 * q), 1)
        while m <= D and B * m + q * m * m < 2 * a:
            m += 1
        return m

    # c < 0：第 k 天之后生长量掉到 1，前段线性、后段按 1 米计
    k = (b - 1) // q  # 最后一个满足 b + x*c >= 1 的天
    m0 = D - k        # 尾部按 1 米生长的天数
    if a <= m0:
        return a  # 只靠尾段每天 1 米就够
    if k == 0:
        return D + 1  # 全程每天只长 1 米，a > D 时完不成
    # 设线性段长 n = m - m0，2(S - m0) = B2*n + q*n*n，解较大根
    B2 = 2 * b + c * (2 * k + 1)
    n = max((isqrt(B2 * B2 + 8 * q * (a - m0)) - B2 + 2 * q - 1) // (2 * q), 1)
    while n <= k and B2 * n + q * n * n < 2 * (a - m0):
        n += 1
    return n + m0


def feasible(D: int, a: list[int], b: list[int], c: list[int],
             children: list[list[int]], depth: list[int], order: list[int]) -> bool:
    """判断能否在第 D 天完成：先算每棵树最晚种下日 t，再检查全树可行的种植日程。"""
    n = len(a)
    t = [0] * n
    for i in range(n):
        m = min_grow_days(a[i], b[i], c[i], D)
        if m > D:
            return False  # 这棵树在 D 天内长不到 a_i
        t[i] = D - m + 1  # 最晚种下日

    # T[u] = depth[u] + 子树内 min(t[w] - depth[w])：祖先必须不晚于它，后代才能全部赶上
    mv = [0] * n
    for u in reversed(order):  # 后序：孩子的 mv 已经算好
        best = t[u] - depth[u]
        for v in children[u]:
            if mv[v] < best:
                best = mv[v]
        mv[u] = best

    # 全部 n 个 T 升序排成日程：第 j 个必须能排在第 j 天（T 升序天然是先祖先的拓扑序）
    rank = sorted(depth[u] + mv[u] for u in range(n))
    return all(val >= j for j, val in enumerate(rank, 1))


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    a = [0] * n
    b = [0] * n
    c = [0] * n
    for i in range(n):
        a[i], b[i], c[i] = next(data), next(data), next(data)

    g: list[list[int]] = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = next(data) - 1, next(data) - 1
        g[u].append(v)
        g[v].append(u)

    # 以 1 号点为根：先序（父在子前）+ 深度 + 子女表，迭代写法避开十万层递归
    parent = [-1] * n
    depth = [0] * n
    children: list[list[int]] = [[] for _ in range(n)]
    order: list[int] = []
    stack = [0]
    parent[0] = -2  # 根标记为已访问
    while stack:
        u = stack.pop()
        order.append(u)
        for v in g[u]:
            if parent[v] == -1:
                parent[v] = u
                depth[v] = depth[u] + 1
                children[u].append(v)
                stack.append(v)

    lo, hi = 1, 10**9  # 题面保证 1e9 天内存在方案
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid, a, b, c, children, depth, order):
            hi = mid
        else:
            lo = mid + 1
    print(lo)


if __name__ == "__main__":
    solve()
