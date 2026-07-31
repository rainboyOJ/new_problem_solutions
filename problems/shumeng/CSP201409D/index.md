---
oj: "shumeng"
problem_id: "CSP201409D"
title: "最优配餐"
description: "以所有分店为多源 BFS 起点，预处理每个格点到最近分店的最短距离并按需求量计费。"
difficulty: "普及-"
date: 2026-07-31 16:21
toc: true
tags: ["BFS", "图", "最短路"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201409D
---

[[TOC]]

### 题意

给定方格图上的多个分店、客户和障碍点。每份餐可以由任意分店配送，配送成本等于路程乘需求量，求最小总成本。

### 思路

先看对每个客户单独 BFS 的暴力：

@include-code(./brute.cpp, cpp)

每个客户独立选择最近分店，因为分店没有配送总量限制，客户之间不会互相影响。若对每个客户单独 BFS，会重复遍历同一张网格。

把所有分店同时加入 BFS 队列，初始距离均为 $0$。BFS 第一次到达某个格点时，得到的就是该格点到任意分店的最短距离 `dist`。之后对每个客户累加 `dist[x][y] * amount` 即可。

样例中客户的最短距离分别为 $8,5,3$，需求量为 $1,3,2$，总成本为 $8+15+6=29$。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

方格图共有 $n^2$ 个格点，每条道路边只会被 BFS 常数次访问，时间复杂度为 $O(n^2+k)$，空间复杂度为 $O(n^2)$。

### 总结

多个起点、边权相同、查询很多时，应把起点一起放入 BFS。一次多源 BFS 共享遍历结果，再用客户需求量作为最后的线性权重。
