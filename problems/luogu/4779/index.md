---
oj: "luogu"
problem_id: "P4779"
title: "【模板】单源最短路径（标准版）"
description: "在非负权有向图上使用堆优化 Dijkstra，每次取出当前距离最小的未确定点并松弛出边。"
difficulty: "普及/提高-"
date: 2026-07-06 20:42
toc: true
tags: ["图论", "最短路", "Dijkstra", "优先队列", "模板题"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4779
---

[[TOC]]

### 题意

给出一个有向非负权图和源点 `s`，求从 `s` 到每个点的最短距离。

数据保证从 `s` 可以到达所有点。

### 思路

先看一个小数据朴素解：

@include-code(./brute.cpp, cpp)

`brute.cpp` 使用 Bellman-Ford 思路，反复枚举所有边做松弛。它容易理解，但复杂度是 $O(nm)$，面对 $n=10^5$, $m=2\times10^5$ 不够。

本题边权非负，所以可以使用 Dijkstra。

核心思想是：

1. `dist[u]` 表示当前已知从源点到 `u` 的最短距离上界；
2. 每次从优先队列中取出 `dist` 最小的点 `u`；
3. 一旦 `u` 被确定，之后不会再变小；
4. 用 `u` 的所有出边 `(u,v,w)` 尝试更新 `dist[v]`。

因为 C++ 的 `priority_queue` 默认是大根堆，所以结构体里把比较写成 `dist > other.dist`，让距离更小的状态优先弹出。

图用链式前向星存储，适合大规模边表，也符合竞赛模板写法。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O((n+m)\log n)$
- 空间复杂度：$O(n + m)$

### 总结

Dijkstra 适用于非负权最短路。模板的关键是：优先队列取当前最短点、出边松弛、已经确定的点不再重复处理。
