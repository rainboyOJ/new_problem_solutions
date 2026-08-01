---
oj: "shumeng"
problem_id: "CSP202506B"
title: "机器人复健指南"
description: "把八个方向理解为马步移动，用 BFS 求出不超过 k 步可达的方格数量。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["数学", "几何", "模拟"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202506B
difficulty: "未知"
---

[[TOC]]

### 题意

机器人在 `n*n` 方格中，每次按马步 `(+-1,+-2)` 或 `(+-2,+-1)` 移动，求从 `(x,y)` 出发不超过 `k` 步可到达的方格数。

### 思路

把每个方格看成图上的一个节点，把八种马步看成边。从起点做 BFS，记录每个方格的最短步数，统计距离不超过 `k` 的节点即可。由于 `n<=100`，图最多只有 `10000` 个节点，直接 BFS 足够。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间、空间复杂度均为 `O(1)`。

### 总结

识别八方向移动的切比雪夫距离后，二维搜索可以直接化为两个一维区间计数。
