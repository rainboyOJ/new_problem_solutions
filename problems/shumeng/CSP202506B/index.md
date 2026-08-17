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
---

[[TOC]]

## 形式化题目

在 $n \times n$ 的网格中从 $(x,y)$ 出发，每次可以向八个方向之一移动（位移为 $(\pm1,\pm2)$ 或 $(\pm2,\pm1)$，即马步），不能走出网格。求不超过 $k$ 步能到达的格子总数（含起点）。

## 思路

每个格子是图上的一个节点，八种马步是节点之间的边。从起点做 BFS 求最短步数，统计步数不超过 $k$ 的格子即可。

### 为什么 BFS

马步移动每次代价相同，BFS 先入队的路径一定最短，所以每个格子第一次被访问时就记录到了最少步数。步数达到 $k$ 的格子不再扩展。

### 边界处理

跳出的方向通过范围检查排除；已访问的格子用 `distance != -1` 判重，避免重复入队。由于 $n,k \le 100$，图最多 $10^4$ 个节点，BFS 完全可行。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

图有 $n^2$ 个节点，每个节点检查 8 条边，时间与空间复杂度均为 $O(n^2)$。

## 总结

本题是标准图 BFS，难点只在把八方向位移和边界条件写对。把位移写成两个数组 `dx/dy` 统一枚举，既简洁又不容易漏方向。