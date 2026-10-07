#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:35
# update_at: 2026-10-08 06:35

import sys

# 抢点顺序的编码：权值 w = 2 - 度数 降序排好后，下标 0,2,4...（Alice 先手）取 +w，其余取 -w。
# 双方偏好一致，都是优先抢当前权值最大的点：抢到既得 +w，又让对手少得 -w，一进一出值 2w。


def optimal_difference(deg: list[int]) -> int:
    """按双方最优策略算 K_A - K_B：收益已被分解成逐点线性项，只需按权值大小轮流抢。"""
    weights = sorted((2 - d for d in deg[1:]), reverse=True)  # deg[0] 是占位格，切片跳过
    # Σ w_i = 2n - 2(n-1) = 2 恒为偶数，任意加符号都不改奇偶，故整除精确（负数亦然）
    return sum(w if i % 2 == 0 else -w for i, w in enumerate(weights)) // 2


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    deg = [0] * (n + 1)             # deg[v] = 点 v 的度数，下标从 1 与题面点号对齐
    edge_count = n - 1              # 题面写「接下来 N 行」是笔误，N 点树只有 N-1 条边
    for _ in range(edge_count):
        u, v = next(data), next(data)
        deg[u] += 1
        deg[v] += 1

    print(optimal_difference(deg))


if __name__ == "__main__":
    solve()
