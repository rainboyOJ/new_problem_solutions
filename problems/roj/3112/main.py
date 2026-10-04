#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:53
# update_at: 2026-10-01 18:04

import sys
from array import array
from collections.abc import Iterator

NEG = -(1 << 60)  # 空区间的最大子段和；合法答案不小于 -1000*5e5，这里远比它小


def build_leaves(t: memoryview, data: Iterator[int], n: int, base: int) -> None:
    """写叶子和内部节点，自底向上建树。"""
    for i in range(n):
        c = (base + i) << 2
        v = next(data)
        t[c] = t[c + 1] = t[c + 2] = t[c + 3] = v
    for p in range(base - 1, 0, -1):
        c = p << 2
        a = p << 3  # 左孩子 2p 的槽位起点
        s1, p1, u1, b1 = t[a], t[a + 1], t[a + 2], t[a + 3]
        s2, p2, u2, b2 = t[a + 4], t[a + 5], t[a + 6], t[a + 7]
        t[c] = s1 + s2
        x = s1 + p2
        t[c + 1] = p1 if p1 > x else x  # pre = max(左 pre, 左 sum + 右 pre)
        x = s2 + u1
        t[c + 2] = u2 if u2 > x else x  # suf = max(右 suf, 右 sum + 左 suf)
        b = b1 if b1 > b2 else b2
        x = u1 + p2
        t[c + 3] = b if b > x else x  # best = max(左 best, 右 best, 左 suf + 右 pre)


def query(t: memoryview, base: int, l: int, r: int) -> int:
    """区间最大连续子段和：把 [l, r) 拆成若干节点，分左右两段归并。"""
    l += base
    r += base
    ls = 0  # 左暂存区的 sum，按"空区间"起步，所以是 0
    lp = lu = lb = rp = rb = NEG  # 两侧贴边量与空区间初值；右暂存区只留 pre/best
    while l < r:
        if l & 1:
            c = l << 2
            u = lu  # 先存旧 suf：合并式里必须用归属左段的旧值
            x = ls + t[c + 1]
            lp = lp if lp > x else x
            x = t[c] + u
            lu = t[c + 2] if t[c + 2] > x else x
            x = u + t[c + 1]
            b = lb if lb > t[c + 3] else t[c + 3]
            lb = b if b > x else x
            ls += t[c]
            l += 1
        if r & 1:
            r -= 1
            c = r << 2
            p = rp  # 同理，先存旧 pre
            x = t[c] + p
            rp = t[c + 1] if t[c + 1] > x else x
            x = t[c + 2] + p
            b = rb if rb > t[c + 3] else t[c + 3]
            rb = b if b > x else x
        l >>= 1
        r >>= 1
    b = lb if lb > rb else rb  # 左暂存区在右、右暂存区在左，只有跨界的 lu+rp 相连
    x = lu + rp
    return b if b > x else x


def update(t: memoryview, base: int, i: int, v: int) -> None:
    """单点修改：改写叶子，再沿父链逐层重新合并。"""
    c = (base + i) << 2
    t[c] = t[c + 1] = t[c + 2] = t[c + 3] = v
    p = (base + i) >> 1
    while p:
        c = p << 2
        a = p << 3
        s1, p1, u1, b1 = t[a], t[a + 1], t[a + 2], t[a + 3]
        s2, p2, u2, b2 = t[a + 4], t[a + 5], t[a + 6], t[a + 7]
        t[c] = s1 + s2
        x = s1 + p2
        t[c + 1] = p1 if p1 > x else x
        x = s2 + u1
        t[c + 2] = u2 if u2 > x else x
        b = b1 if b1 > b2 else b2
        x = u1 + p2
        t[c + 3] = b if b > x else x
        p >>= 1


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    base = 1 << (n - 1).bit_length()  # 叶子层长度取到 >= n 的 2 的幂
    # 一条线段树节点摊平成 4 个槽位 sum/pre/suf/best；数组按 8*base 个 int64 预留。
    # 补位叶子的 best 仍是 0，但它所在的整块区间都超出 [0, n)，查询永远选不到。
    t = memoryview(array('q', [0]) * (8 * base))

    build_leaves(t, data, n, base)

    out: list[str] = []
    for _ in range(m):
        k, x, y = next(data), next(data), next(data)
        if k == 1:
            if x > y:
                x, y = y, x
            out.append(str(query(t, base, x - 1, y)))
        else:
            update(t, base, x - 1, y)

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
