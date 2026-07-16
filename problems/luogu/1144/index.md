---
oj: "luogu"
problem_id: "P1144"
title: "最短路计数"
description: "BFS 分层并在最短层边上累加方案数，支持重边。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
toc: true
tags: ["BFS", "最短路计数", "前向星", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1144
---

[[TOC]]

### 题意

无向无权图中，统计 1 到每个点的最短路径条数。

### 思路

BFS 首次访问确定最短距离。对边 `u-v`，若 `dist[v]=dist[u]+1`，所有到 `u` 的最短路都能扩展成到 `v` 的最短路；重边会被分别遍历，正好分别计数。

### Python 知识

- 百万点、两百万边用 `array` 前向星控制内存。
- `array` 加游标模拟队列，避免大量 deque 整数对象。
- 输出按 8192 行分块，控制字符串峰值内存。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n+m)`，空间 `O(n+m)`。

### 总结

无权最短路计数只在相邻 BFS 层之间累加方案。
