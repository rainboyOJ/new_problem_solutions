---
oj: "luogu"
problem_id: "P2865"
title: "[USACO06NOV] Roadblocks G"
description: "Dijkstra 同时维护每点严格不同的最短与次短距离。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
toc: true
tags: ["次短路", "Dijkstra", "最短路", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2865
---

[[TOC]]

### 题意

求从 1 到 `n` 严格长于最短路的最小路径长度，路径允许回退。

### 思路

每个节点保存 `shortest` 和 `second`。新候选若小于最短，就先把旧最短交换出来，再尝试作为次短；只有满足 `shortest < candidate < second` 才更新次短。

### Python 知识

- 多重赋值完成旧最短与候选的交换。
- 一个最小堆同时处理最短和次短状态。
- 严格不等号排除与最短路等长的另一条路径。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O((n+m)log n)`，空间 `O(n+m)`。

### 总结

次短路不是“第二条被找到的路径”，而是严格大于最短值的最小距离。
