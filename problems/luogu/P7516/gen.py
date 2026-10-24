#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    n = random.randint(2, 6)
    # 随机边数
    max_m = n * (n - 1)
    m = random.randint(1, min(12, max_m))
    
    edges = set()
    edge_list = []
    while len(edge_list) < m:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u != v and (u, v) not in edges:
            edges.add((u, v))
            edge_list.append((u, v))
            
    print(f"{n} {m}")
    for u, v in edge_list:
        print(f"{u} {v}")


if __name__ == "__main__":
    main()
