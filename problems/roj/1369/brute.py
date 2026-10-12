#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-12
# update_at: 2026-10-12
#
# 暴力程序(pythonic 短写法): 枚举所有合并顺序, 验证"先合并最小的两堆"最优
# 只能跑很小的 n (合并顺序有 (2n-3)!! 种, n=7 就有 10395 种)

from itertools import combinations


def dfs(cur, cost):
    """任选两堆合并, 生成器 yield 出每种合并顺序的总代价"""
    if len(cur) == 1:                     # 只剩一堆, 一种合并顺序走完
        yield cost
        return
    for i, j in combinations(range(len(cur)), 2):
        rest = [cur[k] for k in range(len(cur)) if k not in (i, j)]
        yield from dfs(rest + [cur[i] + cur[j]], cost + cur[i] + cur[j])


n = int(input())
a = list(map(int, input().split()))
costs = sorted(dfs(a, 0))                 # 所有合并顺序的总代价, 从小到大
print(f"合并顺序共 {len(costs)} 种, 总代价从小到大:")
print(*costs)
print("最小总代价 =", costs[0])
