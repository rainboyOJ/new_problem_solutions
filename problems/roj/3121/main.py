#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

# 主席树用三个平行数组存全部节点：下标即节点编号，0 号是"空节点"哨兵
lc: list[int] = [0]   # 左儿子编号
rc: list[int] = [0]   # 右儿子编号
cnt: list[int] = [0]  # 子树内数的个数
roots: list[int] = [0]  # roots[i] = 插入前 i 个数后的树根


def insert(prev: int, lo: int, hi: int, pos: int) -> int:
    """在 prev 版本上把离散化下标 pos 的计数 +1，返回新版本节点编号。"""
    node = len(cnt)
    lc.append(lc[prev])
    rc.append(rc[prev])
    cnt.append(cnt[prev] + 1)
    if hi - lo > 1:
        mid = (lo + hi) // 2
        if pos < mid:
            lc[node] = insert(lc[prev], lo, mid, pos)
        else:
            rc[node] = insert(rc[prev], mid, hi, pos)
    return node


def kth(u: int, v: int, k: int, lo: int, hi: int) -> int:
    """在值域 [lo,hi) 上，求版本区间 (u,v]（第 v 个前缀减第 u 个前缀）的第 k 小的离散化下标。"""
    while hi - lo > 1:
        mid = (lo + hi) // 2
        left_cnt = cnt[lc[v]] - cnt[lc[u]]  # 值落在左半区的个数
        if k <= left_cnt:
            u, v, hi = lc[u], lc[v], mid
        else:
            k -= left_cnt
            u, v, lo = rc[u], rc[v], mid
    return lo


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    a = [next(data) for _ in range(n)]

    # 离散化：值域压到 [0, len(vals))
    vals = sorted(set(a))
    rk = {v: i for i, v in enumerate(vals)}

    # 每个前缀建一个版本，共 n 次插入、每次 O(log n) 个新节点
    for x in a:
        roots.append(insert(roots[-1], 0, len(vals), rk[x]))

    out: list[str] = []
    for _ in range(m):
        l, r, k = next(data), next(data), next(data)
        # 区间 [l,r] 的第 k 小 = 前缀 r 减前缀 l-1 后的第 k 小
        out.append(str(vals[kth(roots[l - 1], roots[r], k, 0, len(vals))]))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
