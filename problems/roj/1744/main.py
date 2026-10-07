#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:59
# update_at: 2026-10-07 21:59

import sys
from bisect import bisect_left

INF = 1 << 62  # 无穷大哨兵：真实答案不超过 5e14，远小于它


def upd_min(tree: list[int], pos: int, val: int) -> None:
    """把 0 下标位置 pos 的值下调为 val（前缀最小树状数组只支持"变小"）。"""
    i = pos + 1
    while i < len(tree):
        if val < tree[i]:
            tree[i] = val
        i += i & -i


def qry_min(tree: list[int], pos: int) -> int:
    """询问 0..pos 的最小值；pos < 0 表示区间为空，返回 INF。"""
    res = INF
    i = pos + 1
    while i > 0:
        if tree[i] < res:
            res = tree[i]
        i -= i & -i
    return res


def min_total(h: list[int]) -> int:
    """返回把台阶分给两条从地面出发的链后所需的最小总体力值。

    维护 f(x) = 前 i 个台阶里，第 i 个台阶是某条链末尾、另一条链末尾高度为 x 的最小体力。
    接在 i 后面只是全体加 |Δ|（懒加 add）；换链则把另一条链接到 H_i 上，
    代价是锥形下包络 φ(h) = min( h + min_{x≤h}(f(x)-x), -h + min_{x>h}(f(x)+x) )。
    两棵树状数组分别维护 f(x)-x 与 f(x)+x，单点下调键 H_{i-1}。
    """
    xs = sorted({0, *h})                    # 候选的另一条链末尾高度：地面 0 加上所有台阶高度
    r = len(xs)
    tree_a = [INF] * (r + 1)                # f(x) - x 的前缀最小
    tree_b = [INF] * (r + 1)                # f(x) + x 的前缀最小（下标反转后查 x > h 的部分）

    add = 0                                 # 全局懒加：所有状态共同的增量
    ans = h[0]                              # f_1：第 1 个台阶自成一链，另一条停在地面
    k0 = bisect_left(xs, 0)
    upd_min(tree_a, k0, h[0])
    upd_min(tree_b, r - 1 - k0, h[0])

    for i in range(1, len(h)):
        c = abs(h[i] - h[i - 1])            # 接在同一条链后面的增量
        cur = h[i]
        pos = bisect_left(xs, cur)
        t = cur + qry_min(tree_a, pos) + add                    # x ≤ cur 一侧
        other = -cur + qry_min(tree_b, r - 2 - pos) + add       # x > cur 一侧
        if other < t:
            t = other
        ans = min(ans + c, t)               # 换链后键 H_{i-1} 的新值就是 t
        add += c
        k = bisect_left(xs, h[i - 1])
        base = t - add
        upd_min(tree_a, k, base - xs[k])
        upd_min(tree_b, r - 1 - k, base + xs[k])

    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    h = [next(data) for _ in range(n)]
    print(min_total(h))


if __name__ == "__main__":
    solve()
