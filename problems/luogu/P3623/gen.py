#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-21 00:00
# update_at: 2026-10-21 00:00
# 随机生成小图：n 个点、m 条 0/1 混合类型的边，k 在 0..n-1 里取。
# 一半数据先造一棵随机生成树（保证连通），另一半完全随机（图可能不连通，
# 或 k 超出可行范围），从而保证有相当比例的无解数据。
import random


def main():
    random.seed()
    n = random.randint(1, 7)
    max_m = n * (n - 1) // 2
    mode = random.random()

    if mode < 0.5:
        # 连通图：先铺一棵随机生成树（边类型随机），再补随机边（不与已有边重）
        edges = {}
        nodes = list(range(1, n + 1))
        random.shuffle(nodes)
        for i in range(1, n):
            v = random.randint(0, i - 1)
            edges[(min(nodes[i], nodes[v]), max(nodes[i], nodes[v]))] = random.randint(0, 1)
        extra = random.randint(0, max_m - (n - 1))
        for _ in range(extra):
            u = random.randint(1, n)
            v = random.randint(1, n)
            if u == v:
                continue
            key = (min(u, v), max(u, v))
            if key in edges:
                continue
            edges[key] = random.randint(0, 1)
        m = len(edges)
    elif mode < 0.85:
        # 随机图：可能不连通（无解的一种来源）
        m = random.randint(1, max(max_m, 1))
        edges = {}
        for _ in range(m):
            u = random.randint(1, n)
            v = random.randint(1, n)
            if u == v:
                continue
            key = (min(u, v), max(u, v))
            edges[key] = random.randint(0, 1)
        m = len(edges)
    else:
        # 特意压低鹅卵石路数量：先铺生成树全用水泥路，再只放极少量鹅卵石路，
        # 让"k 偏大"时必然无解（need > k 的另一面：鹅卵石路不够 k 条可进树）。
        edges = {}
        nodes = list(range(1, n + 1))
        random.shuffle(nodes)
        for i in range(1, n):
            v = random.randint(0, i - 1)
            edges[(min(nodes[i], nodes[v]), max(nodes[i], nodes[v]))] = 1
        if n >= 2 and random.random() < 0.6:
            u = random.randint(1, n)
            v = random.randint(1, n)
            if u != v:
                edges[(min(u, v), max(u, v))] = 0
        m = len(edges)

    if m == 0:
        m = 1  # 题面 m >= 1：退化的情况下补一条自环以外无法做到，这里改为单点图+1条重复边
        u = random.randint(1, n)
        v = 1 if u != 1 else min(2, n)
        if u == v:
            n = 2
            u, v = 1, 2
        edges[(min(u, v), max(u, v))] = random.randint(0, 1)
        m = 1

    k = random.randint(0, n - 1)
    print(n, m, k)
    for (u, v), c in edges.items():
        print(u, v, c)


if __name__ == "__main__":
    main()
