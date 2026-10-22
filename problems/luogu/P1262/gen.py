#!/usr/bin/env python3
"""P1262 [POI 1996 R3] 间谍网络 数据生成器。

按题面保证生成：
  - 1 <= p <= n <= 3000，p 行「编号 价格」，价格 <= 20000，编号互不相同；
  - 1 <= r <= 8000，每行两个 1..n 的编号。

结构上分四种模式，覆盖几种关键形态：
  chain   —— 一条长链，考验强连通分量的深度与可达传播
  ring    —— 一个大环加少量出边，整张图缩成一个分量
  random  —— 随机稀疏图，分量结构零散
  dag     —— 只允许小编号指向大编号，图无环，每个点自成分量
并混入少量自环与重复边（题面没有禁止，真实数据里常见）。
"""
import random
import sys

MAX_N = 3000
MAX_R = 8000
MAX_PRICE = 20000


def gen_chain(n, r):
    """长链 1 -> 2 -> ... -> n，补若干随机边把 r 凑够。"""
    edges = [(i, i + 1) for i in range(1, n)]
    while len(edges) < r:
        edges.append((random.randint(1, n), random.randint(1, n)))
    return edges[:r]


def gen_ring(n, r):
    """一个大环 n -> 1 收口，整图强连通。"""
    edges = [(i, i + 1) for i in range(1, n)]
    edges.append((n, 1))
    while len(edges) < r:
        edges.append((random.randint(1, n), random.randint(1, n)))
    return edges[:r]


def gen_random(n, r):
    """随机图，自环与重边都可能出现。"""
    return [(random.randint(1, n), random.randint(1, n)) for _ in range(r)]


def gen_dag(n, r):
    """只允许小编号指向大编号，保证无环，每个点各成一个分量。"""
    edges = []
    if n >= 2:
        for i in range(1, n):
            j = random.randint(i + 1, n)
            edges.append((i, j))
    while len(edges) < r:
        u = random.randint(1, n - 1)
        v = random.randint(u + 1, n)
        edges.append((u, v))
    random.shuffle(edges)
    return edges[:r]


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
    random.seed(seed)

    mode = random.choice(["chain", "ring", "random", "dag"])
    n = random.randint(1, 12) if random.random() < 0.6 else random.randint(1, MAX_N)

    # 可收买人数：偏向多买（这样更容易出现有解），偶尔只给很少的人标价
    if n == 1:
        p = 1
    elif random.random() < 0.75:
        p = random.randint(max(1, n // 2), n)
    else:
        p = random.randint(1, min(n, 3))

    # r 必须 >= 1；n=1 时边只能是自环
    max_edges = MAX_R
    r = random.randint(1, max(1, min(max_edges, n * 3 if n > 1 else 1)))

    if mode == "chain" and n >= 2:
        edges = gen_chain(n, r)
    elif mode == "ring" and n >= 2:
        edges = gen_ring(n, r)
    elif mode == "dag" and n >= 2:
        edges = gen_dag(n, r)
    else:
        edges = gen_random(n, r)

    buyers = random.sample(range(1, n + 1), p)

    out = [str(n), str(p)]
    for v in buyers:
        # 价格允许重复，也允许取到上界
        price = random.choice([1, 2, 3, 5, 10, 100, MAX_PRICE, random.randint(1, MAX_PRICE)])
        out.append(f"{v} {price}")
    out.append(str(len(edges)))
    for u, v in edges:
        out.append(f"{u} {v}")

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
