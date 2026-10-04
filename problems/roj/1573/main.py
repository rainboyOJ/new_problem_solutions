#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 19:18
# update_at: 2026-09-30 19:18

import sys
from collections import deque


def plan_separations(a: list[int]) -> tuple[list[list[int]], list[list[int]]]:
    """区间 DP：dp[l][r] 是区间 [l, r] 分离-合体的最大总价值，cut[l][r] 记录取到最大值的最左分离点。"""
    n = len(a)
    dp = [[0] * n for _ in range(n)]
    cut = [[0] * n for _ in range(n)]

    for length in range(2, n + 1):  # 短区间先算，转移只依赖更短的区间
        for l in range(n - length + 1):
            r = l + length - 1
            ends = a[l] + a[r]  # 合体收益里的“区间左右端点价值之和”
            best, best_k = -1, l
            for k in range(l, r):  # 从左往右枚举，严格大于才替换：平手取最左分离点
                total = dp[l][k] + dp[k + 1][r] + ends * a[k]
                if total > best:
                    best, best_k = total, k
            dp[l][r], cut[l][r] = best, best_k

    return dp, cut


def walk_levels(cut: list[list[int]]) -> list[int]:
    """把分离树按分离阶段（层）从左到右走一遍，产出各分离点的 1 基区域编号。"""
    n = len(cut)
    order: list[int] = []
    queue: deque[tuple[int, int]] = deque([(0, n - 1)] if n > 1 else [])
    while queue:
        l, r = queue.popleft()
        k = cut[l][r]
        order.append(k + 1)
        if l < k:  # 左子区间长度 >= 2 才还需要再分离
            queue.append((l, k))
        if k + 1 < r:  # 右子区间长度 >= 2 才还需要再分离
            queue.append((k + 1, r))
    return order


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]  # 0 基化：a[i] 是区域 i+1 的金钥匙价值
    dp, cut = plan_separations(a)
    print(dp[0][n - 1])
    print(' '.join(map(str, walk_levels(cut))))


if __name__ == "__main__":
    solve()
