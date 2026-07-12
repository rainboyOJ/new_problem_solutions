---
oj: "luogu"
problem_id: "P3366"
title: "【模板】最小生成树"
description: "使用 Kruskal 算法按边权从小到大选不成环的边，并用并查集维护连通块。"
difficulty: "普及/提高-"
date: 2026-01-03 09:38
toc: true
tags: ["模板", "最小生成树", "Kruskal", "并查集", "图论"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3366
---

[[TOC]]

### 题意

给定一个无向带权图，求最小生成树权值和。

如果图不连通，输出 `orz`。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

正式做法使用 Kruskal。

把所有边按权值从小到大排序。依次考虑每条边：如果这条边连接的是两个不同连通块，就把它加入生成树；否则加入它会成环，跳过。

连通块用并查集维护。

最后如果选出的边数是 `n-1`，说明得到了最小生成树；否则图不连通。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序复杂度为：

```text
O(m log m)
```

并查集操作近似线性，空间复杂度为 $O(n+m)$。

### 总结

Kruskal 的核心是：每次选择当前最小的、连接两个不同连通块的边。

并查集负责快速判断一条边是否会成环。
