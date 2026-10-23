#!/usr/bin/env python3
"""
gen.py：为 P4630 生成随机测试数据
- 支持生成树、带环图、带割点图
- n<=20 时适合对拍
"""
import random
import sys

def gen_tree(n: int):
    """生成一棵随机树"""
    edges = []
    for i in range(2, n+1):
        p = random.randint(1, i-1)
        edges.append((p, i))
    return edges

def gen_random_graph(n: int, m: int, ensure_connect=True):
    """生成简单无向图，m 为期望边数上限"""
    edges_set = set()
    edges = []
    # 先连成树保证连通
    if ensure_connect:
        t = gen_tree(n)
        for a,b in t:
            if a > b: a,b = b,a
            edges_set.add((a,b))
            edges.append((a,b))
    # 再随机加边
    attempts = 0
    while len(edges) < m and attempts < m*5:
        a = random.randint(1, n)
        b = random.randint(1, n)
        if a == b: 
            attempts += 1
            continue
        if a > b: a,b = b,a
        if (a,b) in edges_set:
            attempts += 1
            continue
        edges_set.add((a,b))
        edges.append((a,b))
        attempts += 1
    return edges

def main():
    random.seed()
    if len(sys.argv) >= 3:
        n = int(sys.argv[1])
        m = int(sys.argv[2])
    else:
        # 默认小数据，适合对拍
        n = random.randint(3, 12)
        m = random.randint(n-1, min(n*(n-1)//2, n+5))
    edges = gen_random_graph(n, m, ensure_connect=True)
    print(n, len(edges))
    for a,b in edges:
        print(a, b)

if __name__ == "__main__":
    main()
