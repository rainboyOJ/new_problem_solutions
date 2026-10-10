#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:02
# update_at: 2026-10-07 21:02

import sys

MOD = 10 ** 9 + 7  # 答案的模数；首位块的 9 种选择不参与取幂

# 分层并查集：layers[k] 这一层刻画的是"以 i 开头、长度 2^k 的区间"之间的相等关系，
# 所以层号 k 唯一决定了元素含义，下放时不必再携带区间长度；下标 0 留空不用。
type Par = list[int]    # 一层的父指针表
type Size = list[int]   # 一层的连通块大小表


def find(par: Par, x: int) -> int:
    """找 x 所在集合的代表元，顺路做路径减半压缩。"""
    while par[x] != x:
        par[x] = par[par[x]]
        x = par[x]
    return x


def unite(par: Par, size: Size, a: int, b: int) -> None:
    """把 a、b 两个集合合并（按大小启发式，摊还近似 O(α)）。"""
    a, b = find(par, a), find(par, b)
    if a == b:
        return
    if size[a] < size[b]:
        a, b = b, a
    par[b] = a
    size[a] += size[b]


def add_constraint(layers: list[Par], sizes: list[Size], l1: int, r1: int, l2: int, r2: int) -> None:
    """把一条"子串相等"限制压成两次区间合并。

    取 k = floor(log2 L)，两段长度 2^k 的窗口各自从两端对齐，因为 2*2^k >= L
    它们必然重叠并盖满 [l1,r1] 与 [l2,r2]，所以与"整段相等"完全等价。
    """
    k = (r1 - l1 + 1).bit_length() - 1
    step = 1 << k
    unite(layers[k], sizes[k], l1, l2)
    unite(layers[k], sizes[k], r1 - step + 1, r2 - step + 1)


def push_down(layers: list[Par], sizes: list[Size], n: int, k: int) -> None:
    """把第 k 层的相等关系下放到第 k-1 层：两个 2^k 区间相等 ⟹ 两对半长区间分别相等。"""
    par, size = layers[k], sizes[k]
    span, half = 1 << k, 1 << (k - 1)
    for i in range(1, n - span + 2):  # i 的合法范围即 i + span - 1 <= n
        root = find(par, i)
        if root == i:
            continue  # i 自己就是代表元，没有信息要往下传
        unite(layers[k - 1], sizes[k - 1], i, root)
        unite(layers[k - 1], sizes[k - 1], i + half, root + half)


def answer_after_merges(layers: list[Par], n: int) -> int:
    """由完全下放后的第 0 层相等关系得答案：首位所在块只能取 1..9，其余每块各 0..9。"""
    blocks = sum(1 for i in range(1, n + 1) if find(layers[0], i) == i)  # 自由变量个数
    return 9 * pow(10, blocks - 1, MOD) % MOD


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    max_log = n.bit_length() - 1  # floor(log2 n)，实际用到的最高层号
    layers: list[Par] = [list(range(n + 1)) for _ in range(max_log + 1)]
    sizes: list[Size] = [[1] * (n + 1) for _ in range(max_log + 1)]

    for _ in range(m):
        l1, r1, l2, r2 = next(data), next(data), next(data), next(data)
        add_constraint(layers, sizes, l1, r1, l2, r2)

    for k in range(max_log, 0, -1):
        push_down(layers, sizes, n, k)

    print(answer_after_merges(layers, n))


if __name__ == "__main__":
    solve()
