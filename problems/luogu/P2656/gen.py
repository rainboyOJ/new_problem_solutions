#!/usr/bin/env python3
import random

def main():
    # 生成 3~4 个点，3~5 条边，适度包含环
    n = random.randint(3, 4)
    m = random.randint(3, 5)
    edges = []
    for _ in range(m):
        u = random.randint(1, n)
        v = random.randint(1, n)
        w = random.randint(0, 10)
        # 恢复系数 0.0 ~ 0.5
        k = round(random.choice([0.0, 0.2, 0.3, 0.5]), 1)
        edges.append((u, v, w, k))
    
    s = random.randint(1, n)
    print(f"{n} {m}")
    for u, v, w, k in edges:
        print(f"{u} {v} {w} {k}")
    print(s)

if __name__ == '__main__':
    main()
