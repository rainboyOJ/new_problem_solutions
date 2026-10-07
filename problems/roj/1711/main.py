#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 17:46
# update_at: 2026-10-07 18:05

import sys
from array import array
from collections.abc import Iterator
from itertools import islice

BIG = 2 * 10**9  # 哨兵：比单条费用的上限 10^9 大，且放得进 int32；本题是完全图，不会真的取到

type Weights = array  # 平铺的 (n+1)×(n+1) 对称邻接矩阵，w[a*V+b] 是边 (a,b) 的权


def build_weights(n: int, data: Iterator[int]) -> Weights:
    """把输入的三角形费用摊成对称邻接矩阵：边 (a,b)（a<b）的权是题面的 c[a+1][b]。"""
    V = n + 1
    w = array('i', [BIG]) * (V * V)  # 单条费用 <= 10^9，int32 够用，矩阵只要 16 MB
    for i in range(1, n + 1):
        row_len = n + 1 - i                         # 题面第 i 行有 n+1-i 个费用
        row = array('i', islice(data, row_len))
        w[(i - 1) * V + i:i * V] = row              # 上三角：w[i-1][j] = c[i][j]
        start = i * V + i - 1                       # 下三角 w[j][i-1]（j ≥ i）的首个下标
        w[start:start + len(row) * V:V] = row       # 按列步长 V 写入，保持矩阵对称
    return w


def mst(w: Weights, V: int) -> int:
    """完全图上跑朴素 Prim：每轮取未入树的最近点，并用切片整体松弛，返回总权。"""
    dist = [BIG] * V          # dist[u] = 未入树的点 u 到当前树的最小边权
    dist[0] = 0               # 点 0 是前缀和 S_0 = 0，从它出发
    unused = list(range(V))
    total = 0
    for _ in range(V):
        v = min(unused, key=dist.__getitem__)       # 未入树的最近点
        unused.remove(v)
        total += dist[v]
        dist[:v] = map(min, dist[:v], w[v::V])                          # u < v：矩阵第 v 列
        dist[v + 1:] = map(min, dist[v + 1:], w[v * V + v + 1:(v + 1) * V])  # u > v：第 v 行
    return total


def solve() -> None:
    # 先把 2·10^6 个整数压进 array：这样分词产生的字节对象能立刻释放，
    # 否则它们会和 16 MB 的矩阵同时驻留，峰值内存多出约 110 MB。
    nums = array('i', map(int, sys.stdin.buffer.read().split()))
    n = nums[0]
    print(mst(build_weights(n, islice(nums, 1, None)), n + 1))


if __name__ == "__main__":
    solve()
