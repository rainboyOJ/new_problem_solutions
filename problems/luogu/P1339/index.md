---
oj: "luogu"
problem_id: "P1339"
title: "[USACO09OCT] Heat Wave G"
description: "标准正权无向图单源最短路，直接从起点 s 跑一次 Dijkstra，输出到终点 t 的距离即可。"
difficulty: "普及-"
date: 2026-06-20 03:21
toc: true
tags: ["最短路", "图论", "堆"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1339
---

[[TOC]]

### 题意

给一张带正边权的无向图，要求输出从 `s` 到 `t` 的最短路长度。

### 思路

先看一个最直接的小数据暴力：

@include-code(./brute.cpp, cpp)

暴力做法可以用 Floyd：

1. 先求任意两点最短路
2. 最后直接输出 `dist[s][t]`

但这题其实就是最标准的单源最短路模板题。

题目特征很明确：

- 无向图
- 边权都是正数
- 只问一对起点终点

所以直接从 `s` 出发跑一次 Dijkstra 即可。

记 `dist[x]` 表示从 `s` 到 `x` 的最短路，那么答案就是：

- `dist[t]`

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

堆优化 Dijkstra 的复杂度：

- $O((N + M) \log N)$

空间复杂度：

- $O(N + M)$

### 总结

这题没有额外建模，重点就是识别：

- 单源
- 正边权
- 稀疏图

一旦看到这三个信号，基本就应该直接想到堆优化 Dijkstra。
