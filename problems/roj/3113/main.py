#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 17:52
# update_at: 2026-10-01 17:52

import sys
from math import gcd


def solve() -> None:
    src = sys.stdin.buffer.read().split()
    n, m = int(src[0]), int(src[1])
    a = [0] + [int(x) for x in src[2:2 + n]]

    # 差分：b[i] = a[i] - a[i-1]，区间加 [l,r] 变成 b[l] += d、b[r+1] -= d 两个单点改
    b = [a[i] - a[i - 1] for i in range(1, n + 1)]

    # zkw 线段树：叶子是 b[i]，内部节点是子树 gcd；补零叶子不影响 gcd
    log = max(1, (n - 1).bit_length())
    size = 1 << log
    tree = [0] * (2 * size)
    tree[size:size + n] = b
    for i in range(size - 1, 0, -1):
        tree[i] = gcd(tree[2 * i], tree[2 * i + 1])

    # 树状数组维护 b 的前缀和（O(n) 建树），a[l] = b[1] + ... + b[l]
    bit = [0] * (n + 1)
    for i in range(1, n + 1):
        bit[i] += b[i - 1]
        if (j := i + (i & -i)) <= n:
            bit[j] += bit[i]

    def update(p: int, d: int) -> None:
        """差分点 b[p] += d，同步更新线段树与树状数组。"""
        i = size + p - 1
        tree[i] += d
        while i > 1:  # 只有到根的一条链会变化，逐层重算 gcd
            i >>= 1
            tree[i] = gcd(tree[2 * i], tree[2 * i + 1])
        i = p
        while i <= n:
            bit[i] += d
            i += i & -i

    def range_gcd(l: int, r: int) -> int:
        """差分 b[l..r]（1-based）的 gcd，内部节点恒为非负。"""
        res, lo, hi = 0, size + l - 1, size + r
        while lo < hi:
            if lo & 1:
                res = gcd(res, tree[lo])
                lo += 1
            if hi & 1:
                hi -= 1
                res = gcd(res, tree[hi])
            lo >>= 1
            hi >>= 1
        return res

    out: list[str] = []
    pos = 2 + n  # 指令在扁平 token 流里的起始下标
    for _ in range(m):
        op, l, r = src[pos], int(src[pos + 1]), int(src[pos + 2])
        pos += 3
        if op == b'C':
            d = int(src[pos])
            pos += 1
            update(l, d)
            if r < n:
                update(r + 1, -d)
        else:
            # gcd(a[l..r]) = gcd(a[l], b[l+1], ..., b[r])，a[l] 用前缀和求出
            s, i = 0, l
            while i:
                s += bit[i]
                i -= i & -i
            res = abs(s)
            if l < r:
                res = gcd(res, range_gcd(l + 1, r))
            out.append(str(res))

    sys.stdout.write('\n'.join(out) + '\n')


if __name__ == "__main__":
    solve()
