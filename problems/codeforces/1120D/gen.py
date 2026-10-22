#!/usr/bin/env python3
"""CF1120D Power Tree 随机数据生成器（小树，供对拍 brute.cpp 使用）。

覆盖四类树形 + 多种权值策略：
  chain    —— 链（只有一个叶子，退化情形，新图退化成一条链）
  star     —— 菊花（根是唯一非叶子点，n-1 个叶子，第二问容易多点并列）
  binary   —— 完全二叉树
  random   —— 随机父亲（形状最杂）
权值策略里 flat / few 会制造大量重复权值 —— 这是测第二问「属于某棵 MST」判定的关键：
同权边在 Kruskal 分组时先判后合，不能互相干扰。

用法：
  python3 gen.py                # 随机（受 DUPAI_SEED 控制可复现）
  python3 gen.py <n> <kind> <weight_mode>   # 指定参数单点复现
"""
import os
import random
import sys


def build_edges(kind, n):
    """返回 n-1 条边 (a, b)，点编号 1..n，1 是根。"""
    edges = []
    if kind == "chain":
        for v in range(2, n + 1):          # 1-2-3-...-n
            edges.append((v - 1, v))
    elif kind == "star":
        for v in range(2, n + 1):          # 1 连所有人
            edges.append((1, v))
    elif kind == "binary":
        for v in range(2, n + 1):          # 完全二叉树：i 的父亲是 i//2
            edges.append((v // 2, v))
    else:  # random
        for v in range(2, n + 1):          # 父亲编号比儿子小 => 以 1 为根且无环
            edges.append((random.randint(max(1, v - 3), v - 1), v))
    return edges


def main():
    # duipai.py 会通过 DUPAI_SEED 给出每组数据的种子，这里接住它以便复现
    seed_env = os.environ.get("DUPAI_SEED")
    if seed_env:
        random.seed(int(seed_env))

    if len(sys.argv) >= 3:
        n = int(sys.argv[1])
        kind = sys.argv[2]
        weight_mode = sys.argv[3] if len(sys.argv) >= 4 else "few"
    else:
        n = random.randint(2, 8)          # brute.cpp 只能处理 n <= 8
        kind = random.choice(["chain", "star", "binary", "random"])
        weight_mode = random.choice(["flat", "few", "mid", "wide"])

    n = max(2, min(n, 8))                 # 强制落在暴力可解范围内

    # 权值策略：
    #   flat —— 全部相同（最极端的重复权值）
    #   few  —— 只取 0..2（大量重复，最考验分组判定）
    #   mid  —— 取 0..5
    #   wide —— 取 0..1e9（几乎处处不同）
    cost = [0] * (n + 1)
    if weight_mode == "flat":
        w = random.randint(0, 5)
        for i in range(1, n + 1):
            cost[i] = w
    elif weight_mode == "few":
        for i in range(1, n + 1):
            cost[i] = random.randint(0, 2)
    elif weight_mode == "mid":
        for i in range(1, n + 1):
            cost[i] = random.randint(0, 5)
    else:
        for i in range(1, n + 1):
            cost[i] = random.randint(0, 10 ** 9)

    out = [str(n), " ".join(str(cost[i]) for i in range(1, n + 1))]
    for a, b in build_edges(kind, n):
        if random.random() < 0.5:         # 随机交换端点顺序，防止解法依赖输入方向
            a, b = b, a
        out.append(f"{a} {b}")
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
