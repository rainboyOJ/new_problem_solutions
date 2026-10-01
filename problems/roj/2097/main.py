#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:10
# update_at: 2026-10-01 09:10

import sys

MOD = 1  # 模数，由 solve 读入后覆盖；树里所有取模都用它
TREE: list[int] = []  # 每个节点存它负责区间的元素和（已取模）
TAG: list[int] = []   # 乘法懒标记，初始全 1：1 = 没有待下推的乘法


def apply_mul(i: int, v: int) -> None:
    """把乘法 v 记到节点 i：区间和乘 v，未下推的旧标记也乘 v。"""
    TREE[i] = TREE[i] * v % MOD
    TAG[i] = TAG[i] * v % MOD


def push_up(i: int) -> None:
    """两个儿子的区间和相加，得到节点 i 的区间和。"""
    TREE[i] = (TREE[i << 1] + TREE[i << 1 | 1]) % MOD


def push_down(i: int) -> None:
    """把节点 i 攒下的乘法标记推给两个儿子，再把自己清成 1。"""
    v = TAG[i]
    if v != 1:
        apply_mul(i << 1, v)
        apply_mul(i << 1 | 1, v)
        TAG[i] = 1


def build(a: list[int], i: int, l: int, r: int) -> None:
    """建树：叶子取 a[l]，内部节点存左右区间和；l、r 是 1-based 下标。"""
    if l == r:
        TREE[i] = a[l] % MOD
        return
    m = (l + r) >> 1
    build(a, i << 1, l, m)
    build(a, i << 1 | 1, m + 1, r)
    push_up(i)


def range_mul(i: int, l: int, r: int, L: int, R: int, v: int) -> None:
    """节点 i 负责的 [l, r] 与目标 [L, R] 相交部分，每个数乘上 v。"""
    if L <= l and r <= R:  # 整段被覆盖：只在本节点打标记，不进孩子
        apply_mul(i, v)
        return
    push_down(i)           # 要进孩子，先把攒下的标记结清
    m = (l + r) >> 1
    if L <= m:
        range_mul(i << 1, l, m, L, R, v)
    if R > m:
        range_mul(i << 1 | 1, m + 1, r, L, R, v)
    push_up(i)


def range_sum(i: int, l: int, r: int, L: int, R: int) -> int:
    """节点 i 负责的 [l, r] 与目标 [L, R] 相交部分的元素和（模 MOD）。"""
    if L <= l and r <= R:
        return TREE[i]
    push_down(i)           # 孩子里可能压着没结算的乘法
    m = (l + r) >> 1
    s = 0
    if L <= m:
        s = range_sum(i << 1, l, m, L, R)
    if R > m:
        s += range_sum(i << 1 | 1, m + 1, r, L, R)
    return s % MOD


def solve() -> None:
    global MOD, TREE, TAG
    data = list(map(int, sys.stdin.buffer.read().split()))
    n, m = data[0], data[1]
    MOD = data[2]

    a = [0] + data[3:3 + n]   # 1-based 序列，第 0 位占位
    TREE = [0] * (n << 2)
    TAG = [1] * (n << 2)
    build(a, 1, 1, n)

    out: list[str] = []
    pos = 3 + n               # 第一条操作在 data 里的下标
    for _ in range(m):
        if data[pos] == 1:    # 1 x y k：区间 [x, y] 每个数乘 k
            x, y, k = data[pos + 1], data[pos + 2], data[pos + 3]
            range_mul(1, 1, n, x, y, k % MOD)  # k 先取模，标记就不会越滚越大
            pos += 4
        else:                 # 2 x y：输出区间 [x, y] 的和
            x, y = data[pos + 1], data[pos + 2]
            out.append(str(range_sum(1, 1, n, x, y)))
            pos += 3

    sys.stdout.write('\n'.join(out))


if __name__ == "__main__":
    solve()
