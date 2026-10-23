#!/usr/bin/env python3
"""
P4819 杀人游戏 随机数据生成器
生成有向图，N<=1e5 M<=3e5 规模的测试数据
"""
import random
import sys


def gen_random_graph(n, m, allow_self=False, allow_multi=False):
    """生成随机有向图"""
    max_possible = n * (n - 1) if not allow_self else n * n
    m = min(m, max_possible)
    edges = set()
    tries = 0
    max_tries = 100000 + m * 10
    for _ in range(m):
        while True:
            tries += 1
            if tries > max_tries:
                break
            u = random.randint(1, n)
            v = random.randint(1, n)
            if not allow_self and u == v:
                continue
            if (u, v) not in edges or allow_multi:
                edges.add((u, v))
                break
        if tries > max_tries:
            break
    return list(edges)


def gen_dag_like(n, m):
    """生成偏向 DAG 的图（少环）"""
    max_possible = n * (n - 1)
    m = min(m, max_possible)
    edges = set()
    tries = 0
    max_tries = 100000 + m * 10
    for _ in range(m):
        while True:
            tries += 1
            if tries > max_tries:
                break
            u = random.randint(1, n)
            v = random.randint(u, n)
            if u != v and (u, v) not in edges:
                edges.add((u, v))
                break
        if tries > max_tries:
            break
    return list(edges)


def gen_strong_component(n, m):
    """生成一个大 SCC + 少量外部点"""
    max_possible = n * (n - 1)
    m = min(m, max_possible)
    edges = set()
    # 让 1..k 形成强连通
    k = max(2, n // 2)
    for i in range(1, k):
        edges.add((i, i + 1))
    edges.add((k, 1))
    # 随机加边
    tries = 0
    max_tries = 100000 + m * 10
    while len(edges) < m:
        tries += 1
        if tries > max_tries:
            break
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u != v and (u, v) not in edges:
            edges.add((u, v))
    return list(edges)


def main():
    random.seed()
    args = sys.argv[1:]
    n = 100
    m = 200
    mode = "random"

    if len(args) >= 1:
        n = int(args[0])
    if len(args) >= 2:
        m = int(args[1])
    if len(args) >= 3:
        mode = args[2]

    if mode == "dag":
        edges = gen_dag_like(n, m)
    elif mode == "scc":
        edges = gen_strong_component(n, m)
    else:
        edges = gen_random_graph(n, m)

    print(n, len(edges))
    for u, v in edges:
        print(u, v)


if __name__ == "__main__":
    main()
