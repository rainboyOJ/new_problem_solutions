#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:58
# update_at: 2026-10-08 02:58

import sys
from collections import deque

INF = 4 * 10**18  # 无穷大哨兵：评价指数上界约 1e17，4e18 既远离溢出又足够大


def layer(prv: list[int], pre: list[int], gj: int, A: int, B: int, lo: int, hi: int) -> tuple[list[int], int]:
    """算出一层 DP：固定班数时前 i 人的最小评价指数，以及 f[M] 取到最小值时最大的断点。

    转移式 f[i] = gj*pre[i] + min{ prv[k] - gj*pre[k] }（k 取自 [i-B, i-A]），
    括号内只与 k 有关，窗口随 i 单调右移，故用单调队列均摊 O(1) 取最小值。
    """
    n = len(pre) - 1
    cur = [INF] * (n + 1)
    dq = deque()  # 候选断点及其价值 prv[k]-gj*pre[k]，价值沿队列递增
    last_k = -1

    for i in range(lo, hi + 1):
        k = i - A  # 本步新滑入窗口的断点
        if prv[k] < INF:
            val = prv[k] - gj * pre[k]
            # 相等也弹掉队尾：平手时留下更大的 k，最后一个班就更小
            while dq and dq[-1][1] >= val:
                dq.pop()
            dq.append((k, val))
        while dq and dq[0][0] < i - B:  # 队首滑出窗口
            dq.popleft()
        if not dq:
            continue  # 该 i 不可达
        kb, valb = dq[0]
        cur[i] = valb + gj * pre[i]
        if i == n:
            last_k = kb

    return cur, last_k


def solve_case(M: int, N: int, A: int, B: int, X: list[int], G: list[int]) -> tuple[int, int, int]:
    """求一组数据的 (sigma, class, last)：先压评价指数，再压班数，最后压末班人数。"""
    avg = sum(X) // M  # 先全部相加再整除，取下整
    pre = [0] * (M + 1)
    for i, v in enumerate(X, 1):
        pre[i] = pre[i - 1] + (v - avg) ** 2

    prv = [INF] * (M + 1)
    prv[0] = 0  # 边界：0 个学生分成 0 个班，评价指数为 0
    best, best_class, best_last = INF, 0, 0

    for j in range(1, min(N, M // A) + 1):  # 每班至少 A 人，班数不会超过 M//A
        cur, last_k = layer(prv, pre, G[j - 1], A, B, j * A, min(M, j * B))
        prv = cur  # 滚动数组：本层结果就是下一层的前驱
        # 严格小于：评价指数相同则保留更小的班数
        if last_k >= 0 and cur[M] < best:
            best, best_class, best_last = cur[M], j, M - last_k

    return best, best_class, best_last


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    ncase = next(data)
    out: list[str] = []

    for _ in range(ncase):
        M, N, A, B = next(data), next(data), next(data), next(data)
        X = [next(data) for _ in range(M)]
        G = [next(data) for _ in range(N)]
        out.append("%d %d %d" % solve_case(M, N, A, B, X, G))

    print("\n".join(out))


if __name__ == "__main__":
    solve()
