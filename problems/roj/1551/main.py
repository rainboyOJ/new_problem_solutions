#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:44
# update_at: 2026-09-30 17:52

import sys

# 懒标记下标：节点挂着的待做变换是"整段先乘 z[MUL] 再加 z[ADD]"，恒等变换为 (1, 0)
MUL, ADD = 0, 1
IDLE = [1, 0]  # 恒等标记：乘 1 加 0，什么都不做


def apply(node: int, ln: int, b: int, c: int, p: int, t: list[int], z: list[list[int]]) -> None:
    """把变换 x -> b*x+c 整段作用到节点：刷新区间和，并把新变换复合进原标记。

    原标记表示孩子还需做 x -> m*x+a；先做它再做新变换复合出
    x -> b*(m*x+a)+c = (b*m)*x + (b*a+c)，因此标记只增不减、始终等价于整段的累计变换。
    """
    t[node] = (b * t[node] + c * ln) % p
    old = z[node]
    z[node] = [old[MUL] * b % p, (old[ADD] * b + c) % p]


def push(node: int, lo: int, hi: int, p: int, t: list[int], z: list[list[int]]) -> None:
    """把本节点的累计变换下推给两个孩子，再把本节点标记还原为恒等。

    只在"未被查询区间整段覆盖"时才会走到这里，此时必有 lo < hi，孩子一定存在。
    """
    b, c = z[node]
    if b == 1 and c == 0:  # 没有挂标记，省掉一次复合
        return
    mid = (lo + hi) >> 1
    apply(node << 1, mid - lo + 1, b, c, p, t, z)
    apply(node << 1 | 1, hi - mid, b, c, p, t, z)
    z[node] = IDLE


def build(node: int, lo: int, hi: int, arr: list[int], t: list[int], p: int) -> None:
    """建树：叶子存单个数，父节点存两个孩子的和（同样取模，保证 t 恒小于 p）。"""
    if lo == hi:
        t[node] = arr[lo - 1]
        return
    mid = (lo + hi) >> 1
    build(node << 1, lo, mid, arr, t, p)
    build(node << 1 | 1, mid + 1, hi, arr, t, p)
    t[node] = (t[node << 1] + t[node << 1 | 1]) % p


def update(node: int, lo: int, hi: int, ql: int, qr: int,
           b: int, c: int, p: int, t: list[int], z: list[list[int]]) -> None:
    """区间套用变换 x -> b*x+c：整段落入就地作用，否则下推后递归两侧并上收区间和。"""
    if ql <= lo and hi <= qr:
        apply(node, hi - lo + 1, b, c, p, t, z)
        return
    push(node, lo, hi, p, t, z)
    mid = (lo + hi) >> 1
    if ql <= mid:  # 只下探真正相交的一侧
        update(node << 1, lo, mid, ql, qr, b, c, p, t, z)
    if qr > mid:
        update(node << 1 | 1, mid + 1, hi, ql, qr, b, c, p, t, z)
    t[node] = (t[node << 1] + t[node << 1 | 1]) % p


def query(node: int, lo: int, hi: int, ql: int, qr: int,
          p: int, t: list[int], z: list[list[int]]) -> int:
    """区间求和模 p：整段落入直接返回，否则下推标记后累加相交两侧。"""
    if ql <= lo and hi <= qr:
        return t[node]
    push(node, lo, hi, p, t, z)
    mid = (lo + hi) >> 1
    total = 0
    if ql <= mid:
        total = query(node << 1, lo, mid, ql, qr, p, t, z)
    if qr > mid:
        total += query(node << 1 | 1, mid + 1, hi, ql, qr, p, t, z)
    return total % p


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, p = next(data), next(data)
    arr = [next(data) % p for _ in range(n)]  # 初始数列先取模，后续所有量都留在模 p 意义下
    t = [0] * (n << 2)                        # 区间和
    z = [list(IDLE) for _ in range(n << 2)]   # 每节点独立一份标记，不能共享同一列表
    build(1, 1, n, arr, t, p)

    out: list[str] = []
    m = next(data)
    for _ in range(m):
        op = next(data)
        l, r = next(data), next(data)
        if op == 3:  # 询问 l..r 的和模 p
            out.append(str(query(1, 1, n, l, r, p, t, z)))
            continue
        c = next(data) % p
        # 操作 1 = 变换 x -> c*x；操作 2 = 变换 x -> x + c
        update(1, 1, n, l, r, c if op == 1 else 1, 0 if op == 1 else c, p, t, z)

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
