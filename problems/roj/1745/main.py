#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 21:03
# update_at: 2026-10-07 21:03

import sys
from bisect import bisect_left, bisect_right

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type Queries = list[tuple[int, int]]  # 询问表，每项是一对 0 起的居民下标


def bit_add(bit: list[int], i: int, v: int) -> None:
    """Fenwick 单点加：把下标 i 上的计数加上 v（下标从 1 开始）。"""
    while i < len(bit):
        bit[i] += v
        i += i & -i


def bit_sum(bit: list[int], i: int) -> int:
    """Fenwick 前缀和：统计年龄坐标落在 [1, i] 内的已插入人数。"""
    total = 0
    while i > 0:
        total += bit[i]
        i -= i & -i
    return total


def leader_counts(order: list[int], rs: list[int], ages: list[int],
                  vals: list[int], k: int) -> list[int]:
    """cnt[u] = 以 u 当队长时小组的最大人数（地位不高于 u、年龄相差不超过 k 的人）。

    按地位升序把人插入年龄树状数组，同地位的人必须整块插完再统一查询，
    否则并列第一的队长会漏掉彼此（题面允许并列第一当队长）。
    """
    n = len(ages)
    pos = [bisect_left(vals, a) + 1 for a in ages]   # 年龄 -> 离散坐标（1 起）
    bit = [0] * (len(vals) + 1)
    cnt = [0] * n
    i = 0
    while i < n:
        j = i
        while j < n and rs[order[j]] == rs[order[i]]:
            bit_add(bit, pos[order[j]], 1)           # 整块插入，保证同地位互相可见
            j += 1
        for t in range(i, j):
            u = order[t]
            lo = bisect_left(vals, ages[u] - k) + 1  # 第一个 >= a_u - k 的坐标
            hi = bisect_right(vals, ages[u] + k)     # 最后一个 <= a_u + k 的坐标
            if lo <= hi:
                cnt[u] = bit_sum(bit, hi) - bit_sum(bit, lo - 1)
            else:
                cnt[u] = 0                           # 年龄区间里没有任何坐标
        i = j
    return cnt


def query_answers(cnt: list[int], order: list[int], rs: list[int], ages: list[int],
                  vals: list[int], queries: Queries, k: int) -> list[int]:
    """离线回答全部询问，返回按输入顺序排列的答案。

    队长 L 合法当且仅当 r_L >= max(r_x, r_y) 且 a_L 同时落在两人的年龄邻域内，
    此时答案就是 cnt[L]；把询问按"队长最小排名"降序排序，指针从地位最高的人
    往回扫，让线段树里的元素只增不减，区间查最大值即可。
    """
    n = len(ages)
    sorted_r = [rs[u] for u in order]            # 按地位升序的地位序列
    pos = [bisect_left(vals, a) for a in ages]   # 线段树坐标从 0 起
    size = 1
    while size < len(vals):
        size <<= 1
    tree = [0] * (2 * size)                      # 下标为年龄坐标的最大值线段树
    plan = []                                    # (队长最小排名, 年龄区间左端, 右端, 询问下标)
    for qi, (x, y) in enumerate(queries):
        start = bisect_left(sorted_r, max(rs[x], rs[y]))          # 排名 >= start 才有资格
        ql = bisect_left(vals, max(ages[x], ages[y]) - k)         # 两个年龄邻域的交
        qr = bisect_right(vals, min(ages[x], ages[y]) + k) - 1
        plan.append((start, ql, qr, qi))

    ans = [0] * len(queries)
    p = n - 1
    for start, ql, qr, qi in sorted(plan, reverse=True):
        while p >= start:
            u = order[p]
            i = size + pos[u]
            while i:
                if cnt[u] > tree[i]:             # 同一坐标可能被多个人写入，取较大者
                    tree[i] = cnt[u]
                i >>= 1
            p -= 1
        best = 0
        left, right = ql + size, qr + size + 1
        while left < right:                      # 迭代式区间最大值
            if left & 1:
                best = max(best, tree[left])
                left += 1
            if right & 1:
                right -= 1
                best = max(best, tree[right])
            left >>= 1
            right >>= 1
        # x、y 一定被合法队长计入，所以最大值小于 2 就说明没有合法队长
        ans[qi] = best if best >= 2 else -1
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    rs = [next(data) for _ in range(n)]
    ages = [next(data) for _ in range(n)]
    q = next(data)
    queries = [(next(data) - 1, next(data) - 1) for _ in range(q)]

    order = sorted(range(n), key=rs.__getitem__)   # 地位升序的居民下标
    vals = sorted(set(ages))                       # 年龄离散化取值表
    cnt = leader_counts(order, rs, ages, vals, k)
    ans = query_answers(cnt, order, rs, ages, vals, queries, k)
    sys.stdout.write('\n'.join(map(str, ans)) + '\n')


if __name__ == "__main__":
    solve()
