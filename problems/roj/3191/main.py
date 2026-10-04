#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 00:34
# update_at: 2026-10-02 00:56

import sys
from array import array
from itertools import chain

NEG = -(1 << 50)  # 非法状态；合法值恒为非负
NO_CHILD = 2      # gain 的初值：没有孩子就付不出"牺牲"，且 max(0, 1 - 2) = 0 正好等价于无穷大


def peel_trees(parent: array, n: int) -> tuple[array, array, array]:
    """剥掉所有不在环上的点，自底向上把每棵挂树压成两个数。

    parent[u] 就是题面的 A[u]；u 的见证者集合恰好是 parent 为 u 的那些点。
    off[v]   v 不投放时，v 的子树（不含 v）最多能投放多少个
    gain[v]  逼 v 的某个孩子不投放所需的最小牺牲，没有孩子时是 NO_CHILD
    返回的 indeg[v] > 0 表示 v 剥不掉，也就是落在某个环上。
    """
    indeg = array('i', bytes(4 * (n + 1)))
    for v in range(1, n + 1):
        indeg[parent[v]] += 1                       # 入度正是 v 的孩子个数
    off = array('i', bytes(4 * (n + 1)))
    gain = array('b', bytes([NO_CHILD]) * (n + 1))
    stack = [v for v in range(1, n + 1) if indeg[v] == 0]  # 环外的叶子先入栈

    while stack:
        v = stack.pop()
        slack = 0 if gain[v] >= 1 else 1 - gain[v]  # 孩子本来未必投放，牺牲可以减免
        p = parent[v]
        off[p] += off[v] + slack
        if slack < gain[p]:
            gain[p] = slack
        indeg[p] -= 1
        if indeg[p] == 0:                           # 孩子都处理完了，v 也成了叶子
            stack.append(p)

    return indeg, off, gain


def ring_best(ring: list[int], off: array, gain: array) -> int:
    """一个环最多能投放多少个。ring 按“孩子在前、父亲在后”排列。

    于是 A[ring[i]] = ring[i-1]：轮到 ring[i] 时，它在环上的见证者 ring[i-1] 已经定好，
    dp0 / dp1 就是“ring[i] 不投放 / 投放”的最优值。环尾 ring[-1] 是环首 ring[0] 的
    见证者，故枚举环尾状态两次，让环首取到对应的初值，并在链尾取回对应的一维。
    """
    head = ring[0]
    on_tree = off[head] + 1 - gain[head] if gain[head] < NO_CHILD else NEG  # 只靠挂树当见证
    if len(ring) == 1:                              # 自环：唯一的环上候选是自己，不能当见证
        return off[head] if off[head] > on_tree else on_tree

    best = NEG
    for tail_off in (True, False):
        dp0 = off[head]
        dp1 = off[head] + 1 if tail_off else on_tree
        for v in ring[1:]:
            free = dp0 if dp0 > dp1 else dp1         # 环上前驱不投放，v 才可以投放
            by_tree = dp1 - gain[v] if gain[v] < NO_CHILD else NEG
            dp1 = off[v] + 1 + (dp0 if dp0 > by_tree else by_tree)
            dp0 = free + off[v]                      # v 不投放，挂树各自取最优
        cur = dp0 if tail_off else dp1               # 环尾不投放取 dp0，投放取 dp1
        if cur > best:
            best = cur
    return best


def best_total(parent: array, n: int) -> int:
    """整片基环树森林最多能投放多少个元素。"""
    indeg, off, gain = peel_trees(parent, n)
    total = 0
    for s in range(1, n + 1):
        if indeg[s] == 0:                            # 已被剥掉，贡献早已算进它所属的环
            continue
        ring: list[int] = []
        u = s
        while indeg[u] > 0:                          # 顺着 parent 走，孩子总在父亲前面
            ring.append(u)
            indeg[u] = 0                             # 打标记，免得同一个环被走第二遍
            u = parent[u]
        total += ring_best(ring, off, gain)
    return total


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)                                   # 第一行是元素个数
    parent = array('i', chain([0], data))            # 用 0 占位，使 A[i] 落在下标 i
    sys.stdout.write(str(best_total(parent, n)) + "\n")


if __name__ == "__main__":
    solve()
