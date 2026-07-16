---
oj: "luogu"
problem_id: "P1395"
title: "会议"
description: "用子树大小和换根 DP 求树上距离和最小的节点。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["树形 DP", "换根 DP", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1395
---

[[TOC]]

### 题意

选择会议点，使所有节点到它的距离和最小；相同距离时取编号小的点。

### 思路

以 1 为根求 `subtree[u]` 和 `sum[1]`。根从 `u` 移到儿子 `v` 时，`v` 子树内的点距离减 1，其余点距离加 1，所以 `sum[v] = sum[u] + n - 2*subtree[v]`。

### Python 知识

- `reversed(order[1:])` 完成自底向上子树统计。
- `min(range(...), key=lambda node: (...))` 同时处理最小值和编号 tie-break。
- 非递归遍历不会在链形树上触发调用栈限制。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n)`，空间 `O(n)`。

### 总结

换根公式把每条边两侧的规模差直接变成距离和变化量。
