---
oj: "luogu"
problem_id: "P3275"
title: "[SCOI2011] 糖果"
description: "把下界约束建成 0/1 边，SCC 判严格环后在缩点 DAG 上求最长路。"
difficulty: "提高"
date: 2026-07-17 03:00
toc: true
tags: ["差分约束", "强连通分量", "DAG", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3275
---

[[TOC]]

### 题意

满足五类大小关系且每人至少一颗糖，求最小糖果总数。

### 思路

约束写成 `x_v >= x_u+w`，其中严格大于是权 1，否则权 0。若同一 SCC 内存在权 1 边，就形成正环而无解；否则缩点图是 DAG，从每个分量初值 1 做最长路，分量内节点取相同最小值。

### Python 知识

- 显式栈实现 Kosaraju 两遍 DFS，避免递归深度问题。
- `deque` 做缩点 DAG 的拓扑排序。
- 分量大小乘分量最长路值，直接得到总糖果数。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

SCC 与 DAG DP 均为 `O(n+m)`，空间 `O(n+m)`。

### 总结

0/1 下界约束中，矛盾恰好是强连通分量里出现严格增长边。
