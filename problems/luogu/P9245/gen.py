#!/usr/bin/env python3
"""P9245 景区导游 的随机数据生成器，输出到 stdout。

格式与题目一致：

    第一行: N K
    之后 N-1 行: u v t      (一条摆渡车线路)
    最后一行: A1 A2 ... AK  (原定游览线路, 两两不同)

可复现：设置环境变量 DUPAI_SEED=<整数>（或 `python3 gen.py <seed>`）就固定随机
种子，同一个种子一定生成同一份数据；不指定时随机取种子，并把种子打印到 stderr，
失败样例可以直接拿这个种子重放。

brute.cpp 对每一个待跳过的位置都要把 K-1 段路径各搜一次整棵树，
总代价约 O(K^2 * N)，所以生成器把 N 与 K 都压在小规模。
下面用 seed % 8 选择树形和数据形态，尽量覆盖：

  0. 随机树（最普通的形态）
  1. 链（树上最深的形态，检验倍增跳深度是否正确）
  2. 菊花（根连所有点，深度只有 2）
  3. 完全二叉树（结构规则，LCA 分支多）
  4. 毛毛虫（一条主链 + 挂在链上的叶子）
  5. 双链“十字路口”（路径必然经过少数几个点，路径和高度重合）
  6. 极小数据 N = K = 2
  7. 满 K：A 是 1..N 的一个排列，N 与 K 相同

边权在 [1, 100000] 内随机，偶尔用很小的边权去撞“路径长度相同”的平局。
"""

import os
import random
import sys

# brute.cpp 用固定大小的数组，生成器不能超过这个规模。
MAX_N = 300
MAX_W = 100000


def random_tree(n, rnd):
    """随机树：每个点 i 随机连到 [1, i-1] 中的某个点。"""
    edges = []
    for v in range(2, n + 1):
        u = rnd.randint(1, v - 1)
        edges.append((u, v))
    return edges


def chain_tree(n, rnd):
    """链：1 - 2 - 3 - ... - n，树上最深的形态。"""
    return [(i, i + 1) for i in range(1, n)]


def star_tree(n, rnd):
    """菊花：1 号点连其他所有点，深度最多 2。"""
    return [(1, v) for v in range(2, n + 1)]


def binary_tree(n, rnd):
    """完全二叉树：i 的父亲是 i // 2。"""
    return [(v // 2, v) for v in range(2, n + 1)]


def caterpillar_tree(n, rnd):
    """毛毛虫：先取一条主链，再把剩下的点全挂到主链的点上。"""
    spine = max(2, (n + 1) // 2)
    edges = [(i, i + 1) for i in range(1, spine)]
    for v in range(spine + 1, n + 1):
        u = rnd.randint(1, spine)
        edges.append((u, v))
    return edges


def double_chain_tree(n, rnd):
    """两条长链在端点附近接起来：从一条链走到另一条链必须经过接点。"""
    first = max(1, n // 2)
    edges = [(i, i + 1) for i in range(1, first)]
    joint = rnd.randint(max(1, first // 2), first)
    edges.append((joint, first + 1))
    for v in range(first + 1, n):
        edges.append((v, v + 1))
    return edges


SHAPES = [
    random_tree,
    chain_tree,
    star_tree,
    binary_tree,
    caterpillar_tree,
    double_chain_tree,
]


def build(n, shape_index, rnd):
    """按指定形态造一棵 n 个点的树，并给每条边随机一个边权。"""
    base_edges = SHAPES[shape_index % len(SHAPES)](n, rnd)
    edges = []
    for u, v in base_edges:
        if rnd.random() < 0.2:
            w = rnd.randint(1, 3)          # 小边权：容易出现相等的路径长度
        else:
            w = rnd.randint(1, MAX_W)
        if rnd.random() < 0.5:
            u, v = v, u                    # 打乱端点顺序
        edges.append((u, v, w))
    return edges


def pick_k(n, rnd):
    """选择 K：偏向小 K（暴力快），但也保留 K 接近 N 的情形。"""
    roll = rnd.random()
    if roll < 0.25:
        return 2
    if roll < 0.6:
        return rnd.randint(2, min(n, 10))
    if roll < 0.85:
        return rnd.randint(2, n)
    return n                               # K = N：A 是 1..N 的一个排列


def emit(n, k, edges, order, out):
    out.append("%d %d" % (n, k))
    for u, v, w in edges:
        out.append("%d %d %d" % (u, v, w))
    out.append(" ".join(str(x) for x in order))


def main():
    # 指定了种子（命令行参数优先，其次是环境变量）就固定下来；
    # 没指定时随机取一个，并把种子打印到 stderr，失败时可以照原样重放。
    seed_text = sys.argv[1] if len(sys.argv) > 1 else os.environ.get("DUPAI_SEED")
    if seed_text is None:
        seed = random.randrange(1, 10 ** 9)
        print("# DUPAI_SEED=%d" % seed, file=sys.stderr)
    else:
        seed = int(seed_text)
    rnd = random.Random(seed)

    roll = seed % (len(SHAPES) + 2)

    if roll == len(SHAPES):
        # 极小数据：N = K = 2，只有一条边，用来核对边界。
        n, k = 2, 2
        edges = [(1, 2, rnd.randint(1, 5))]
        order = [1, 2]
    elif roll == len(SHAPES) + 1:
        # K = N：A 是 1..N 的一个排列，把所有景点都走一遍。
        n = rnd.randint(2, 30)
        k = n
        edges = build(n, rnd.randint(0, len(SHAPES) - 1), rnd)
        order = rnd.sample(range(1, n + 1), n)
    else:
        n = rnd.randint(2, min(MAX_N, 40)) if rnd.random() < 0.6 else rnd.randint(2, MAX_N)
        k = pick_k(n, rnd)
        edges = build(n, roll, rnd)
        order = rnd.sample(range(1, n + 1), k)

    out = []
    emit(n, k, edges, order, out)
    print("\n".join(out))


if __name__ == "__main__":
    main()
