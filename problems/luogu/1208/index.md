---
oj: "luogu"
problem_id: "P1208"
title: "[USACO1.3] 混合牛奶 Mixing Milk"
description: "按单价从低到高购买牛奶，每次尽量买满当前最便宜农民的供应量。"
difficulty: "入门"
date: 2026-07-15 22:15
toc: true
tags: ["贪心", "排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1208
---

[[TOC]]

### 题意

需要购买 `N` 单位牛奶，有 `M` 个农民。每个农民给出单价 `P_i` 和最多能卖的数量 `A_i`。总供应量保证足够，求买够 `N` 单位牛奶的最小花费。

### 思路

每单位牛奶没有区别，只是价格不同。因此越便宜的牛奶越应该优先买。

如果某个方案先买了更贵的牛奶，同时还剩下更便宜的牛奶没买，那么把这部分购买量换到便宜农民那里，总数量不变，花费只会下降。所以最优方案一定可以按单价从低到高购买。

做法：

1. 把农民按单价排序；
2. 从低价到高价扫描；
3. 当前农民能买多少就买多少，但不能超过剩余需求；
4. 需求变成 `0` 时结束。

### Python 知识

- `farmers.append((price, amount))` 用元组保存一条记录。
- `farmers.sort()` 会先按单价排序，单价相同再按数量排序；本题单价相同的顺序不影响答案。
- `min(need, amount)` 表示当前最多购买量。

这是典型排序贪心题，跳过 `brute.py`，用样例和交换论证说明正确性。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

排序复杂度是 $O(M \log M)$，扫描复杂度是 $O(M)$。

空间复杂度是 $O(M)$。

### 总结

当每个单位物品没有差异，只是购买价格不同，最小花费通常就是按单价升序贪心购买。
