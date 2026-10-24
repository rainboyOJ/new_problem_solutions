#!/usr/bin/env python3
import random
import sys


def main():
    random.seed()
    # 生成适合对拍的小规模有向图（n <= 8，确保朴素暴力的显式长度枚举与搜索能快速完成且答案落在小长度范围内）
    n = random.randint(2, 8)
    # 保证 1 到 n 至少有一条连通路径
    # 先随机生成一条 1 到 n 的通路
    path_len = random.randint(1, n)
    # 随机选择中间节点（允许重复以模拟自环/回路）
    path = [1]
    for _ in range(path_len - 1):
        path.append(random.randint(1, n))
    path.append(n)

    edges = []
    for i in range(len(path) - 1):
        edges.append((path[i], path[i + 1]))

    # 额外添加若干随机有向边（包含自环与重边）
    extra_edges = random.randint(0, 15)
    for _ in range(extra_edges):
        u = random.randint(1, n)
        v = random.randint(1, n)
        edges.append((u, v))

    m = len(edges)
    print(f"{n} {m}")
    for u, v in edges:
        print(f"{u} {v}")


if __name__ == "__main__":
    main()
