---
oj: "luogu"
problem_id: "P3366"
title: "【模板】最小生成树"
description: "使用 Kruskal 算法按边权从小到大选不成环的边，并用并查集维护连通块。"
difficulty: "普及/提高-"
date: 2026-01-03 09:38
updated: 2026-10-07 12:15
toc: true
tags: ["模板", "最小生成树", "Kruskal", "并查集", "图论"]
categories: []
pre:
  - oj: "luogu"
    problem_id: "P2097"
    reason: "B 的成环判断复用 A 的「并查集维护连通块、find 比较代表元判断是否同块」这一步（不同连通块才把边加入生成树），再叠加 A 未教的边权排序贪心与选满 n-1 条判定不连通。"
  - oj: "roj"
    problem_id: "1346"
    reason: "B 直接把 A 教的代表元判定（find 相同即同块）用作是否成环的判断，并把 A 用于建块的 union 换成按边权依次合并两端，A 是纯并查集模板，B 在其上叠加排序与选边流程，难度差 2 级"
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
