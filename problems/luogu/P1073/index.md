---
oj: "luogu"
problem_id: "P1073"
title: "[NOIP 2009 提高组] 最优贸易"
description: "在有向图上同时传播路径最低买价和最大已获利润。"
difficulty: "提高"
date: 2026-07-17 03:00
toc: true
tags: ["图上 DP", "最短路", "队列松弛", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1073
---

[[TOC]]

### 题意

沿 1 到 `n` 的可重复有向路线，最多买卖一次，求最大利润。

### 思路

每个节点维护到达它的路径最低价格 `minimum` 和最大已获利润 `profit`。沿边传播时，新最低价取较小值，新利润取旧利润与“当前城市售价减此前最低价”的较大值；任一状态改善就重新入队，直到收敛。

### Python 知识

- 两个单调状态数组共同描述到达节点后的最优信息。
- `bytearray` 保存是否在队列，避免重复入队。
- 双向道路按输入类型补反向边。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

队列松弛最坏较高，价格仅到 100 时状态下降次数有限；空间 `O(n+m)`。

### 总结

“先买后卖”沿路径只需记最低历史价格和最大历史差值。
