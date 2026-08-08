---
oj: "luogu"
problem_id: "P3128"
title: "[USACO15DEC] Max Flow P"
description: "用 LCA 和树上点差分统计所有路径经过每个牧场的次数。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["LCA", "树上差分", "树", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3128
---

[[TOC]]

### 题意

给出许多树上路径，求经过路径最多的节点流量。

### 思路

对路径 `u-v`、`g=lca(u,v)` 做点差分：`diff[u] += 1`、`diff[v] += 1`、`diff[g] -= 1`、`diff[parent[g]] -= 1`。最后按 DFS 逆序把子树差分累加到父亲，得到每个节点经过的路径数。

### Python 知识

- 倍增表用 `array("i")`，差分用普通整数列表便于累加。
- `reversed(order)` 是树上后序汇总的简洁写法。
- LCA 函数同时服务路径差分和距离层级逻辑。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

预处理 `O(n log n)`，每条路径 `O(log n)`，总空间 `O(n log n)`。

### 总结

树上路径“经过次数”可以把逐条路径标记变成端点差分和一次后序累加。
