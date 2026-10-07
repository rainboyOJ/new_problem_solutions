---
oj: "luogu"
problem_id: "P3275"
title: "[SCOI2011] 糖果"
description: "把下界约束建成 0/1 边，SCC 判严格环后在缩点 DAG 上求最长路。"
difficulty: "提高"
date: 2026-07-17 03:00
updated: 2026-10-06 07:45
toc: true
tags: ["差分约束", "强连通分量", "DAG", "python"]
categories: []
pre:
  - oj: "shumeng"
    problem_id: "CSP201509D"
    reason: "B 沿用 A 的把互相可达关系归结为强连通分量并求出分量这一步，用来判定分量内权 1 边构成正环，再叠加差分约束与缩点 DAG 最长路"
  - oj: "HDU"
    problem_id: "3836"
    reason: "B 的正环判定与最长路都建立在 A 的「求 SCC 并缩点成 DAG」这一步上（同一 SCC 内出现权 1 边即正环无解，缩点 DAG 上再做 DP），再叠加 A 未教的差分约束 x_v>=x_u+w 建图与分量大小乘最长路求总糖果。"
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
