---
oj: "shumeng"
problem_id: "CSP201509D"
title: "高速公路"
description: "用 Tarjan 分解强连通分量，分量内任意两城都构成便利城市对。"
difficulty: "普及+/提高"
date: 2026-07-31 16:21
toc: true
tags: ["强连通分量", "Tarjan", "有向图"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201509D
---

[[TOC]]

### 题意

统计有向高速公路图中能够互相到达的无序城市对数量。

### 思路

小数据可从每个城市 BFS 判断可达关系：

@include-code(./brute.cpp, cpp)

互相可达的城市恰好位于同一个强连通分量。Tarjan 算法得到一个大小为 $s$ 的分量时，它贡献 $\binom{s}{2}=s(s-1)/2$ 对，累加所有分量即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n+m)$，空间复杂度为 $O(n+m)$。

### 总结

“双向可达”直接对应强连通分量。求出分量大小后，城市对数量由组合数一次计算。
