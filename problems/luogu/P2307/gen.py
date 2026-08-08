#!/usr/bin/env python3
import random

def main():
    random.seed()
    # 生成 2~4 组数据
    for _ in range(random.randint(2, 4)):
        n_nodes = random.randint(1, 8)
        # 用 1..n 的房间，随机生成边
        edges = []
        # 50% 生成一棵树（合法），50% 加一条多余边（可能非法）
        for i in range(2, n_nodes + 1):
            edges.append((i, random.randint(1, i - 1)))
        if random.random() < 0.5 and n_nodes > 1:
            edges.append((random.randint(1, n_nodes), random.randint(1, n_nodes)))
        random.shuffle(edges)
        for u, v in edges:
            print(u, v)
        print(0, 0)
        print()
    print(-1, -1)

if __name__ == "__main__":
    main()
