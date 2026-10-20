#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-17 01:40
# update_at: 2026-10-20 16:40
#
# main.py：社交网络。求每个点的重要度 I(v) = sum_{s!=v, t!=v} C(s,t)(v) / C(s,t)。
# 需要两个量：任意两点的最短路条数，以及经过 v 的最短路条数。
#
# 第一个量在 Floyd 里同步维护。Floyd 第 k 轮只在上一轮结论上加一件事：放开 k 这个中转点，
# 所以每轮的候选恰好是两类——不经 k 的（上一轮已有）和经 k 的（本轮新算）。两类互斥，
# 所以等长时累加不会重复；一条经 k 的路径拆成 i->k 与 k->j 两段，两段独立选择，
# 所以条数相乘。
# 必须跳过 i == k 和 j == k：dist[i][k] 在 i == k 时是 0，那条"路径"原地没动，
# 它既不算"经 k"也不算"不经 k"，互斥前提被破坏，累加就会重复计数。
#
# 第二个量用距离的加性判断：v 在 s->t 的某条最短路上 <=> dist[s][v]+dist[v][t]==dist[s][t]。
# 此时 C(s,t)(v) = cnt[s][v] * cnt[v][t]，因为 v 在路径上的位置确定，拆分唯一。

import sys

INF = 10**18  # 整数哨兵；Python int 任意精度，路径数相乘不会溢出


def floyd_with_count(n: int, edges: list[tuple[int, int, int]]):
    """返回 (dist, cnt)：dist[i][j] 为最短距离，cnt[i][j] 为最短路条数。点编号 0..n-1。"""
    dist = [[INF] * n for _ in range(n)]
    cnt = [[0] * n for _ in range(n)]
    for i in range(n):
        dist[i][i] = 0
        cnt[i][i] = 1  # 自己到自己有一条长度 0 的平凡路径

    for u, v, w in edges:
        # 题面保证任意两点间最多一条边，直接赋值
        dist[u][v] = dist[v][u] = w
        cnt[u][v] = cnt[v][u] = 1

    for k in range(n):
        through = dist[k]  # dist[k][*]，缓存行引用
        cnt_through = cnt[k]
        for i in range(n):
            if i == k:
                continue  # 必须跳过：否则 dist[i][k]=0 的平凡路径会被重复累加
            row = dist[i]
            cnt_row = cnt[i]
            bridge = row[k]  # dist[i][k]
            if bridge == INF:
                continue  # i 到 k 不可达，经 k 中转没有意义
            cnt_to_k = cnt_row[k]
            for j in range(n):
                if j == k or i == j:
                    continue
                candidate = bridge + through[j]
                if candidate > row[j]:
                    continue  # 不是更优，连乘积都不必算
                ways = cnt_to_k * cnt_through[j]
                if candidate < row[j]:
                    # 经 k 更短：旧走法全部作废，条数替换
                    row[j] = candidate
                    cnt_row[j] = ways
                else:
                    # 经 k 一样短：一批新最短路，条数累加（两类路径互斥，不会重复）
                    cnt_row[j] += ways

    return dist, cnt


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    edges: list[tuple[int, int, int]] = []
    for _ in range(m):
        u, v, w = next(data), next(data), next(data)
        edges.append((u - 1, v - 1, w))  # 题面编号 1..n，统一转成 0..n-1

    dist, cnt = floyd_with_count(n, edges)

    for v in range(n):
        importance = 0.0
        for s in range(n):
            if s == v:
                continue
            cnt_sv = cnt[s][v]
            dist_sv = dist[s][v]
            for t in range(n):
                if t == v or t == s:
                    continue
                # v 在 s->t 的某条最短路上 <=> 两段距离之和等于总距离
                if dist_sv + dist[v][t] == dist[s][t]:
                    importance += cnt_sv * cnt[v][t] / cnt[s][t]
        print(f"{importance:.3f}")


if __name__ == "__main__":
    solve()
