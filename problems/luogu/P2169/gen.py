#!/usr/bin/env python3
"""洛谷 P2169 正则表达式 的随机数据生成器。

输出到 stdout，格式与题目一致：第一行 n m，之后 m 行 u v w。

可复现：设置环境变量 DUPAI_SEED=<整数> 可固定随机种子；
不设置时每次运行使用不同种子，便于对拍时覆盖更多情形。
生成器通过 seed % 6 选择不同的数据形态，覆盖：

  0. 极小随机图（含重边、自环）
  1. 有多条随机环、能形成非平凡强连通分量的图
  2. 链状 DAG（不存在任何环）
  3. 稠密小图、边权含 0
  4. 两个大环被长链串起来（1 和 n 可能落在同一个大局域网里）
  5. 退化边界：n = 1，全是自环

每种形态都会先铺一条 1 -> 2 -> ... -> n 的链，保证 1 一定能到达 n，
这样答案总是有限值，对拍比较才有意义。
"""

import os
import random
import sys

# brute.cpp 使用固定大小数组，生成器不能越界。
MAX_N = 60
MAX_M = 400
MAX_W = 20


def emit(n, edges, out):
    """按题目格式输出一张图。"""
    out.append("%d %d" % (n, len(edges)))
    for u, v, w in edges:
        out.append("%d %d %d" % (u, v, w))


def base_chain(n, rnd, edges):
    """铺一条 1->2->...->n 的链，保证终点可达。"""
    for i in range(1, n):
        edges.append((i, i + 1, rnd.randint(1, MAX_W)))


def gen_tiny_random(rnd, out):
    n = rnd.randint(2, 6)
    edges = []
    base_chain(n, rnd, edges)
    for _ in range(rnd.randint(1, 8)):
        u = rnd.randint(1, n)
        v = rnd.randint(1, n)  # 允许 u == v（自环）
        edges.append((u, v, rnd.randint(1, MAX_W)))
    emit(n, edges[:MAX_M], out)


def gen_cycles(rnd, out):
    """随机撒若干条环，环上的点会互相可达，形成真正的局域网。"""
    n = rnd.randint(6, 18)
    edges = []
    base_chain(n, rnd, edges)
    for _ in range(rnd.randint(1, 4)):
        length = rnd.randint(2, min(5, n))
        verts = rnd.sample(range(1, n + 1), length)
        for i in range(length):
            edges.append((verts[i], verts[(i + 1) % length], rnd.randint(1, MAX_W)))
    for _ in range(rnd.randint(0, 8)):
        u = rnd.randint(1, n)
        v = rnd.randint(1, n)
        edges.append((u, v, rnd.randint(1, MAX_W)))
    emit(n, edges[:MAX_M], out)


def gen_dag_chain(rnd, out):
    n = rnd.randint(10, MAX_N)
    edges = []
    base_chain(n, rnd, edges)
    # 只加“从小编号指向大编号”的边，保证无环，环上的免费传输不会出现
    for _ in range(rnd.randint(0, n)):
        u = rnd.randint(1, n - 1)
        v = rnd.randint(u + 1, n)
        edges.append((u, v, rnd.randint(1, MAX_W)))
    emit(n, edges[:MAX_M], out)


def gen_dense(rnd, out):
    n = rnd.randint(5, 12)
    edges = []
    base_chain(n, rnd, edges)
    for _ in range(rnd.randint(2 * n, min(MAX_M, 3 * n))):
        u = rnd.randint(1, n)
        v = rnd.randint(1, n)
        edges.append((u, v, rnd.randint(0, 5)))  # 边权可以为 0
    emit(n, edges[:MAX_M], out)


def gen_two_big_cycles(rnd, out):
    """构造两个大环：1 在大环 A 里，n 在大环 B 里，中间用链相连。"""
    half = rnd.randint(4, 9)
    n = 2 * half + rnd.randint(0, 4)
    edges = []
    # 大环 A：包含 1
    for i in range(1, half + 1):
        edges.append((i, i % half + 1, rnd.randint(1, MAX_W)))
    # 大环 B：包含 n
    for i in range(half + 1, n + 1):
        nxt = (i + 1) if i < n else half + 1
        edges.append((i, nxt, rnd.randint(1, MAX_W)))
    # 把两个环连起来（可能只连一次，也可能来回连形成更大的环）
    for _ in range(rnd.randint(1, 3)):
        a = rnd.randint(1, half)
        b = rnd.randint(half + 1, n)
        edges.append((a, b, rnd.randint(1, MAX_W)))
        if rnd.randint(0, 1) == 1:
            edges.append((b, a, rnd.randint(1, MAX_W)))
    emit(n, edges[:MAX_M], out)


def gen_degenerate(rnd, out):
    """退化边界：n = 1，可能全是自环，答案必须是 0。"""
    n = 1
    edges = []
    for _ in range(rnd.randint(1, 4)):
        edges.append((1, 1, rnd.randint(0, MAX_W)))
    emit(n, edges, out)


GENERATORS = [
    gen_tiny_random,
    gen_cycles,
    gen_dag_chain,
    gen_dense,
    gen_two_big_cycles,
    gen_degenerate,
]


def main():
    seed_text = os.environ.get("DUPAI_SEED")
    if seed_text is None:
        seed = random.randrange(1, 10 ** 9)
    else:
        seed = int(seed_text)

    rnd = random.Random(seed)
    generator = GENERATORS[seed % len(GENERATORS)]

    out = []
    generator(rnd, out)
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
