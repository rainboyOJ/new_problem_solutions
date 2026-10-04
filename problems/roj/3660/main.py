#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 13:44
# update_at: 2026-10-02 13:44

import sys


def max_pairs(rest: list[int], limit: int) -> int:
    """排序单链里最多能拼出多少对（每对长度和 ≥ limit）：双指针，最短 + 最长能拼就拼。"""
    i, j, pairs = 0, len(rest) - 1, 0
    while i < j:
        if rest[i] + rest[j] >= limit:  # 最短 + 最长能拼就拼，省着用长链
            pairs += 1
            i += 1
            j -= 1
        else:                           # 最短的链已无配对可能
            i += 1
    return pairs


def pair_chains(rests: list[int], limit: int) -> tuple[int, int]:
    """把子树伸上来的单链分配成赛道：≥ limit 的单链独立成赛道，其余两两拼接。

    返回 (本结点确定的赛道条数, 剩余可向父结点延伸的最长单链)。
    配对数取最大 p；在这个前提下传上去的链越长越好，
    而「弃掉较大的链、留下较小的」只会让配对更难（交换论证可证单调），
    所以二分出「删掉它后仍能配出 p 对」的最长链当作剩余。
    """
    singles = sum(c >= limit for c in rests)       # ≥ limit 的链各自独立成赛道
    rest = sorted(c for c in rests if c < limit)   # 全部 < limit，拼不出也不够单干
    p = max_pairs(rest, limit)
    leftover = 0                                   # 恰好全部配满时无剩余链
    lo, hi = 0, len(rest) - 1                      # 谓词随下标单调：删得越大越难配
    while lo < hi:
        mid = (lo + hi + 1) // 2
        keeps = max_pairs(rest[:mid] + rest[mid + 1:], limit) >= p  # 删掉 rest[mid] 还能配 p 对吗
        if keeps:
            lo = mid
        else:
            hi = mid - 1
    if p * 2 < len(rest):                          # 有配不出去的弃链，取能弃的最长的那条
        leftover = rest[lo]
    return singles + p, leftover


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)

    adj: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]  # 邻接表：(邻居, 道路长)
    total_len = 0
    for _ in range(n - 1):
        a, b, l = next(data), next(data), next(data)
        adj[a].append((b, l))
        adj[b].append((a, l))
        total_len += l

    # 迭代求「父结点先于子结点」的访问序：n 达 5e4，链形树会把递归爆栈
    parent = [0] * (n + 1)
    order = [1]
    for u in order:  # order 边遍历边增长，父结点必先入序
        for v, _ in adj[u]:
            if v != parent[u]:
                parent[v] = u
                order.append(v)

    def max_tracks(limit: int) -> int:
        """每条赛道长度都 ≥ limit 时，整棵树最多能修出多少条赛道。"""
        total = 0
        up = [0] * (n + 1)  # 结点处拼不出赛道、还能向父结点继续延伸的最长链
        for u in reversed(order):  # 逆序处理，保证算 u 时所有子结点已汇报
            rests = [up[v] + l for v, l in adj[u] if v != parent[u]]
            pairs, longest = pair_chains(rests, limit)
            total += pairs
            up[u] = longest
        return total  # 根结点的剩余链无处延伸，自然作废

    # 二分答案：limit 越大能修的赛道越少，找能满足 m 条的最大 limit
    lo, hi = 1, total_len
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if max_tracks(mid) >= m:
            lo = mid
        else:
            hi = mid - 1
    print(lo)


if __name__ == "__main__":
    solve()
