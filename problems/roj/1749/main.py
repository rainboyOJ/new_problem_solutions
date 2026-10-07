#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:05
# update_at: 2026-10-07 21:05

import sys

MOD = 10 ** 9 + 7  # 题目要求的取模数


def add_range(d: list[int], l: int, r: int, v: int) -> None:
    """在差分数组 d 的闭区间 [l, r] 上整体加 v；l > r 时是空区间，直接跳过。"""
    if l > r or v == 0:
        return
    d[l] = (d[l] + v) % MOD
    d[r + 1] = (d[r + 1] - v) % MOD


def window_max_sum(arr: list[int]) -> list[int]:
    """回答：arr 的所有长度 k 子区间的最大值之和是多少（k = 1..n，对 MOD 取模）。

    每个区间只由它「最右边的那个最大值」代表。下标 i 是区间 [s, e] 的最右最大值，
    当且仅当 L[i] < s <= i <= e < R[i]，其中 L 是左侧最近的严格更大位置、
    R 是右侧最近的大于等于位置。于是 arr[i] 被长度 k 的区间计入
        cnt(k) = min(k, a, b, a+b-k)，a = i - L[i]，b = R[i] - i，
    它关于 k 分三段线性，用两个差分数组一次求出全部 k 的答案。
    """
    n = len(arr) - 1
    lef = [0] * (n + 1)
    rig = [n + 1] * (n + 2)

    stk: list[int] = []  # 单调递减栈，存下标
    for i in range(1, n + 1):
        while stk and arr[stk[-1]] <= arr[i]:
            stk.pop()
        lef[i] = stk[-1] if stk else 0
        stk.append(i)

    stk.clear()
    for i in range(n, 0, -1):
        while stk and arr[stk[-1]] < arr[i]:
            stk.pop()
        rig[i] = stk[-1] if stk else n + 1
        stk.append(i)

    slope = [0] * (n + 3)    # 差分：k 的系数
    const = [0] * (n + 3)    # 差分：常数项
    for i in range(1, n + 1):
        v = arr[i] % MOD
        a, b = i - lef[i], rig[i] - i
        small, big = min(a, b), max(a, b)
        last = a + b - 1                                   # cnt(k) > 0 的最大 k
        add_range(slope, 1, small, v)                      # cnt = k
        add_range(const, small + 1, big, v * small % MOD)  # cnt = small
        add_range(const, big + 1, last, v * (a + b) % MOD)  # cnt = a+b-k
        add_range(slope, big + 1, last, (-v) % MOD)

    out = [0] * (n + 1)
    s1 = s2 = 0  # 斜率前缀、常数前缀
    for k in range(1, n + 1):
        s1 = (s1 + slope[k]) % MOD
        s2 = (s2 + const[k]) % MOD
        out[k] = (s1 * k + s2) % MOD
    return out


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]
    b = [next(data) for _ in range(n)]

    # C[i][j] = (A[i] + i) * (B[j] + j)，两因子恒正，故行列最大值可分开算
    x = [0] + [v + i for i, v in enumerate(a, 1)]
    y = [0] + [v + i for i, v in enumerate(b, 1)]

    sx = window_max_sum(x)
    sy = window_max_sum(y)

    ans = [sx[k] * sy[k] % MOD for k in range(1, n + 1)]
    print(" ".join(map(str, ans)))


if __name__ == "__main__":
    solve()
