#!/usr/bin/env python3
import random
import sys

def main():
    # 生成随机小规模数据用于对拍
    # T 组数据
    T = random.randint(1, 3)
    print(T)
    for _ in range(T):
        n = random.randint(2, 6)
        m = random.randint(n - 1, min(12, n * (n - 1)))
        k = random.randint(0, 3)
        p = 1000000007 # 大质数，避免模为0导致比较复杂

        # 为了保证尽量有通路，先随一个可能包含 1 到 n 的有向图
        edges = set()
        edge_list = []
        
        # 增加一些可能连向各点的边
        attempts = 0
        while len(edges) < m and attempts < 1000:
            attempts += 1
            u = random.randint(1, n)
            v = random.randint(1, n)
            if u != v and (u, v) not in edges:
                edges.add((u, v))
                # 边权倾向于生成少量 0 权边以测试 0 环情况
                w = random.choice([0, 0, 1, 2, 3])
                edge_list.append((u, v, w))

        m = len(edge_list)
        print(f"{n} {m} {k} {p}")
        for u, v, w in edge_list:
            print(f"{u} {v} {w}")

if __name__ == "__main__":
    main()
