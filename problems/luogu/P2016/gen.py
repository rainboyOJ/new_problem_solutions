#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    # 生成小规模树用于与暴力对拍（n 在 1 到 15 之间）
    n = random.randint(1, 15)
    print(n)

    if n == 1:
        print("0 0")
        return

    # 生成包含 0..n-1 的树
    nodes = list(range(n))
    random.shuffle(nodes)

    # 随机连边生成树，并把边定向为无向图中的有向输出（输入要求每条边只出现一次）
    # 我们可以维护每个结点的出边
    adj = {i: [] for i in range(n)}
    for i in range(1, n):
        u = nodes[i]
        # 从已经加入树的点集中随机选一个作为父节点
        parent = nodes[random.randint(0, i - 1)]
        adj[parent].append(u)

    # 按照 0 到 n-1 输出每个结点的边
    # 也可以按随机顺序输出，题面指出：第二行至第 n+1 行，每行描述每个结点信息
    order = list(range(n))
    random.shuffle(order)
    for u in order:
        neighbors = adj[u]
        print(f"{u} {len(neighbors)}", *neighbors)


if __name__ == "__main__":
    main()
