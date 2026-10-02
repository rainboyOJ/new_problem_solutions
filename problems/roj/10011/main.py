#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 18:13
# update_at: 2026-10-02 18:13

import heapq
import sys
from collections.abc import Iterator

INF = float("inf")  # 挨打 0 次的块：一击必杀还白拿升级，性价比视为无穷


def root_tree(g: list[list[int]]) -> list[int]:
    """以 1 为根做迭代 DFS，返回每个点的父亲；1 的父亲记 0。"""
    parent = [0] * len(g)
    parent[1] = -1  # 先占位标记根已访问，遍历完再还原成 0
    stack = [1]
    while stack:
        u = stack.pop()
        for v in g[u]:
            if parent[v] == 0:
                parent[v] = u
                stack.append(v)
    parent[1] = 0
    return parent


def hit_rounds(hp: int, hero_atk: int, monster_def: int) -> int:
    """打死这只怪前英雄要挨的次数：先手打 ceil(hp/(攻-防)) 次，此前挨 t 次反击。"""
    per = hero_atk - monster_def
    return (hp + per - 1) // per - 1


def block_ratio(total_gain: int, total_rounds: int) -> float:
    """块的性价比：每挨一次打能换来多少升级。"""
    return total_gain / total_rounds if total_rounds else INF


def find(f: list[int], x: int) -> int:
    """并查集查块顶，路径压缩。"""
    while f[x] != x:
        f[x] = f[f[x]]
        x = f[x]
    return x


def fight_order(parent: list[int], rounds: list[int], gain: list[int]) -> list[int]:
    """块合并贪心：堆按性价比弹出全局最大的块；块顶的父亲已出战就整块出战
    （块顶先打，子块按弹出先后即性价比降序），否则整块并进父亲所在的块。"""
    n = len(parent) - 1
    f = list(range(n + 1))          # 并查集：指向所在块的块顶
    total_rounds = rounds[:]        # 块累计挨打次数
    total_gain = gain[:]            # 块累计升级
    kids: list[list[int]] = [[] for _ in range(n + 1)]  # 块顶名下已并入的子块
    popped = [False] * (n + 1)      # 块顶弹出过：之后清掉过期堆项
    scheduled = [False] * (n + 1)   # 是否已出战
    scheduled[1] = True             # 1 号点是起点，视为最先出战
    heap = [(-block_ratio(total_gain[i], total_rounds[i]), -i) for i in range(2, n + 1)]
    heapq.heapify(heap)
    order: list[int] = []

    while heap:
        _, neg_u = heapq.heappop(heap)
        u = -neg_u
        if popped[u]:
            continue                # 并块前压入的旧键，块已合并过
        popped[u] = True
        if scheduled[parent[u]]:
            # 父亲已出战：整块立刻出战，块顶最先，子块按并入先后（性价比降序）
            stack = [u]
            while stack:
                x = stack.pop()
                scheduled[x] = True
                order.append(x)
                stack.extend(reversed(kids[x]))
            continue
        # 父亲还没上场：并进父亲的块攒着，合并后的性价比是按挨打次数的加权平均
        p = find(f, parent[u])
        total_gain[p] += total_gain[u]
        total_rounds[p] += total_rounds[u]
        kids[p].append(u)
        f[u] = p
        heapq.heappush(heap, (-block_ratio(total_gain[p], total_rounds[p]), -p))
    return order


def final_hp(order: list[int], hp: int, armor: int, m_atk: list[int],
             rounds: list[int], gain: list[int]) -> int:
    """按出战序列结算血量：每场挨 t×(怪攻-当前防御)；中途阵亡返回 -1。"""
    defense = armor
    for u in order:
        hp -= rounds[u] * (m_atk[u] - defense)
        if hp <= 0:
            return -1
        defense += gain[u]
    return hp


def solve() -> None:
    data: Iterator[int] = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    g: list[list[int]] = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        x, y = next(data), next(data)
        g[x].append(y)
        g[y].append(x)
    hp, hero_atk, armor = next(data), next(data), next(data)

    # 怪物第 k 行对应节点 k+1：血量、攻击、防御、打完提升的等级
    m_atk = [0] * (n + 1)
    rounds = [0] * (n + 1)
    gain = [0] * (n + 1)
    for u in range(2, n + 1):
        b, a, d, v = next(data), next(data), next(data), next(data)
        m_atk[u], gain[u] = a, v
        rounds[u] = hit_rounds(b, hero_atk, d)

    order = fight_order(root_tree(g), rounds, gain)
    print(final_hp(order, hp, armor, m_atk, rounds, gain))


if __name__ == "__main__":
    solve()
