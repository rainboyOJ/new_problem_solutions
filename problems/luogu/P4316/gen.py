#!/usr/bin/env python3
import random
import sys

def generate_dag(n, max_extra_edges):
    # 生成确保 1 可以到达所有点，且所有点都能到达 n 的连通 DAG
    # 最简单可靠的方法：点编号 1 到 n，所有边方向从小号到大号 (u < v)，天然保证 DAG
    # 先建立一条主骨架链 1 -> 2 -> ... -> n，保证从 1 到达所有点，且所有点都能到达 n
    edges = set()
    for i in range(1, n):
        edges.add((i, i + 1))
    
    # 随机添加若干条 u < v 的边
    for _ in range(max_extra_edges):
        u = random.randint(1, n - 1)
        v = random.randint(u + 1, n)
        edges.add((u, v))
        
    m = len(edges)
    edge_list = []
    for u, v in edges:
        w = random.randint(0, 1000)
        edge_list.append((u, v, w))
        
    random.shuffle(edge_list)
    return n, m, edge_list

def main():
    # 小数据规模（用于对拍 brute.cpp，n 范围在 5~14，保证暴力可在短时间内完成）
    n = random.randint(4, 12)
    max_extra = random.randint(1, n)
    n, m, edges = generate_dag(n, max_extra)
    print(f"{n} {m}")
    for u, v, w in edges:
        print(f"{u} {v} {w}")

if __name__ == "__main__":
    main()
