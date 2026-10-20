#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-08-09 06:46
# update_at: 2026-10-20 10:51
#
# main.py：佳佳的魔法药水，求 0 号药水的最小花费与最优方案数。
# 两种得到药水的方式：直接买一份（price[i]），或用配方 A+B->C 合成（cost[A]+cost[B]）。
# 价格都是正数，合成花费严格大于两个原料各自的花费，所以配方是「两个原料都定型才能松弛」
# 的超边，仍可用 Dijkstra 的单调序处理：弹出当前最便宜的药水并定型，再看含它的配方，
# 若另一个原料也已定型就用两者花费之和松弛产物。
# 花费定型后按花费升序统计方案数：买一份算 1 种，每条 cost[A]+cost[B]==cost[C] 的配方
# 贡献 ways[A]*ways[B] 种（两个原料的选法互相独立）。

import sys
from heapq import heapify, heappop, heappush

# 输入以空行结束，所以统一按整数流读到底，再按位置切开
data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]                                  # 药水总数，编号 0..n-1
price = data[1:n + 1]                        # 商店里 1 份 i 号药水的价格
recipes = [tuple(data[index:index + 3]) for index in range(n + 1, len(data), 3)]

# by_ingredient[u]：把 u 当原料的配方下标；同一种原料只登记一次，避免自配方重复
by_ingredient = [[] for _ in range(n)]
for index, (first, second, result) in enumerate(recipes):
    by_ingredient[first].append(index)
    if second != first:
        by_ingredient[second].append(index)

# 第一阶段：Dijkstra 求最小花费。初始候选就是「直接买」。
distance = price[:]
heap = [(value, potion) for potion, value in enumerate(distance)]
heapify(heap)
while heap:
    current, potion = heappop(heap)
    if current != distance[potion]:
        continue                             # 堆里的过期记录，这个药水已有更便宜的花费
    for recipe_index in by_ingredient[potion]:
        first, second, result = recipes[recipe_index]
        # 两个原料此时都已定型（potion 自己刚定型，另一个也定型过才会走到这里），可以松弛
        candidate = distance[first] + distance[second]
        if candidate < distance[result]:
            distance[result] = candidate
            heappush(heap, (candidate, result))

# 第二阶段：按最小花费升序累计方案数
ways = [0] * n
recipes_by_result = [[] for _ in range(n)]
for first, second, result in recipes:
    recipes_by_result[result].append((first, second))

# 最优配方的原料花费都严格小于产物，所以按花费升序保证原料先算完；
# 花费相同的药水之间不可能互为原料，同花费的先后顺序不影响结果
for potion in sorted(range(n), key=distance.__getitem__):
    ways[potion] = price[potion] == distance[potion]      # 直接买一份算 1 种方案
    # 每条满足 cost[A]+cost[B]==cost[C] 的配方，贡献 ways[A]*ways[B] 种组合
    ways[potion] += sum(ways[first] * ways[second] for first, second in recipes_by_result[potion]
                        if distance[first] + distance[second] == distance[potion])

print(distance[0], ways[0])
