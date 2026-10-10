#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 15:58
# update_at: 2026-10-07 16:04

import sys

NO_CHILD = -1  # 01 字典树的空边标记：kids[u][b] 为它表示结点 u 没有走边 b 的儿子


def prefix_xors(a: list[int]) -> list[int]:
    """返回前缀异或表 p，p[i] = a[0] ^ ... ^ a[i-1]，p[0] = 0。"""
    p = [0]
    for v in a:
        p.append(p[-1] ^ v)
    return p


def moment_consts(p: list[int], n: int) -> list[int]:
    """返回对手每个时刻对应的常数 C_i = rol(p[i]) ^ (p[m] ^ p[i])，i 从 0 到 m。

    对手在第 i 个时刻出手时最终值恰好是 rol(x) ^ C_i；rol 是 n 位循环左移。
    """
    full = (1 << n) - 1   # n 位全 1 掩码，把循环左移截回 n 位
    return [
        ((p[i] << 1 & full) | p[i] >> (n - 1)) ^ (p[-1] ^ p[i])
        for i in range(len(p))
    ]


def worst_case(cs: list[int], n: int) -> tuple[int, int]:
    """把 cs 建成 01 字典树后自底向上求：y 能保证的最坏结果值，以及取到它的方案数。"""
    kids = [[NO_CHILD, NO_CHILD]]  # 结点 0 是根，结点编号大的都是后开出来的
    depth = [0]                    # depth[u] = 走到 u 已确定的位数，即 u 所在的层
    for c in cs:
        u = 0
        for k in reversed(range(n)):   # 高位到低位
            b = c >> k & 1
            v = kids[u][b]
            if v == NO_CHILD:          # 这条边还没有，开一个新结点挂上去
                v = len(kids)
                kids[u][b] = v
                kids.append([NO_CHILD, NO_CHILD])
                depth.append(depth[u] + 1)
            u = v

    val = [0] * len(kids)   # val[u]：只看 u 的剩余位，y 能保证的最坏结果值
    cnt = [1] * len(kids)   # cnt[u]：达到 val[u] 的 y 低位方案数，叶子层只剩 1 种
    for u in reversed(range(len(kids))):   # 子结点编号必大于父结点，逆序即自底向上
        if depth[u] == n:                  # 叶子：C 的 n 位已定格，没有剩余位
            continue
        bit = 1 << n - 1 - depth[u]        # 这一位在结果数值里的权重
        lo, hi = kids[u]
        if lo == NO_CHILD or hi == NO_CHILD:
            # 只剩一棵子树：全部 C 这一位相同，y 取反位就让这一位变 1，低位在该子树里继续
            only = hi if lo == NO_CHILD else lo
            val[u], cnt[u] = bit + val[only], cnt[only]
        elif val[lo] == val[hi]:
            # 两棵子树都在：对手能把这一位压成 0；两侧最优值相同，方案数相加
            val[u], cnt[u] = val[lo], cnt[lo] + cnt[hi]
        else:
            best = lo if val[lo] > val[hi] else hi   # 这一位取更优的 y 选侧
            val[u], cnt[u] = val[best], cnt[best]
    return val[0], cnt[0]


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a = [next(data) for _ in range(m)]

    # 记 y = rol(x)，则 rol 是双射，问题变成「选 y 使 min_i (y ^ C_i) 最大」，
    # 求值与计数都可以在 y 上进行，不必换回 x。
    value, count = worst_case(moment_consts(prefix_xors(a), n), n)
    print(value)
    print(count)


if __name__ == "__main__":
    solve()
