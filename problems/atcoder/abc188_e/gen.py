#!/usr/bin/env python3
"""生成 abc188_e 的数据：所有边都满足 x < y 的有向图。

用法：
    python3 gen.py              # 小数据随机图，n <= 60，给 brute.cpp 对拍
    python3 gen.py chain        # 小数据链，n <= 60
    python3 gen.py big          # 全规模随机图 n = m = 2 * 10**5，计时用
    python3 gen.py big-chain    # 全规模链，n = m = 2 * 10**5，压递归深度
"""
import random
import sys

from cyaron import IO, randint

BIG_N = 200000


def random_edges(n, m):
    """在 n 个点上随机取 m 条互不相同、且保证 x < y 的边。"""
    limit = n * (n - 1) // 2
    m = min(m, limit)
    pairs = set()
    while len(pairs) < m:
        x = randint(1, n - 1)
        y = randint(x + 1, n)
        pairs.add((x, y))
    return list(pairs)


def chain_edges(n):
    """1 -> 2 -> ... -> n 的链：最长链长度达到 n，用来压递归深度。"""
    return [(i, i + 1) for i in range(1, n)]


def emit(n, edges, value_limit):
    io = IO(input_file=sys.stdout, disable_output=True)
    io.input_writeln(n, len(edges))
    io.input_writeln([randint(1, value_limit) for _ in range(n)])
    for x, y in edges:
        io.input_writeln(x, y)


def main():
    # 不带参数时在随机图与链之间随机，让对拍同时覆盖一般结构和最长链结构。
    mode = sys.argv[1] if len(sys.argv) > 1 else random.choice(["random", "chain"])
    if mode == "random":
        n = randint(2, 60)
        emit(n, random_edges(n, randint(1, 120)), 100)
    elif mode == "chain":
        n = randint(2, 60)
        emit(n, chain_edges(n), 100)
    elif mode == "big":
        emit(BIG_N, random_edges(BIG_N, BIG_N), 10**9)
    elif mode == "big-chain":
        # 链打底，再补一些跨边，保证 m 也到上限
        extra = BIG_N - (BIG_N - 1)
        emit(BIG_N, chain_edges(BIG_N) + random_edges(BIG_N, extra), 10**9)
    else:
        raise SystemExit("unknown mode: " + mode)


if __name__ == "__main__":
    main()
