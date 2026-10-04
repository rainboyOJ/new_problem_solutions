#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 17:11
# update_at: 2026-09-30 17:16

import sys

FLIP = 1  # 操作 1：区间翻转
ASK = 2   # 操作 2：单点询问


def lowbit(x: int) -> int:
    """取 x 最低位的 1：树状数组每个结点管辖的长度。"""
    return x & -x


def prefix_xor(tree: list[int], i: int) -> int:
    """返回差分的异或前缀和 d[1] ^ ... ^ d[i]，即 a[i] 的当前值。"""
    acc = 0
    while i > 0:
        acc ^= tree[i]
        i -= lowbit(i)
    return acc


def flip(tree: list[int], i: int, size: int) -> None:
    """把差分 d[i] 取反，并向上更新所有管辖到 i 的树状数组结点。"""
    while i <= size:
        tree[i] ^= 1
        i += lowbit(i)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    # 用差分数组 d[i] = a[i] ^ a[i-1] 表示原数组：
    # 区间 [L,R] 翻转只改 d[L] 与 d[R+1]，单点 a[i] 就是 d[1..i] 的异或前缀和。
    # 两种操作都要在线完成，故用异或树状数组维护 d 的前缀异或。
    tree = [0] * (n + 1)
    out: list[str] = []

    for _ in range(m):
        t = next(data)
        if t == FLIP:
            left, right = next(data), next(data)
            flip(tree, left, n)             # 翻转区间左端：开启一段翻转
            if right < n:
                flip(tree, right + 1, n)    # 右端之后撤销翻转；越界端点无需记录
        elif t == ASK:
            out.append(str(prefix_xor(tree, next(data))))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
