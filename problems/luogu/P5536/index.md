---
oj: "luogu"
problem_id: "P5536"
title: "【XR-3】核心城市"
description: "叶层剥离得到每个城市的离叶层数，直接选出最小可行核心半径。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["树", "拓扑剥离", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5536
---

[[TOC]]

### 题意

选择恰好 `k` 个互相连通的核心城市，使非核心城市到核心的最大距离最小。

### 思路

不断删除当前叶子并记录删除层数。删除 `r` 层后剩余节点仍连通，且所有被删节点到剩余部分距离不超过 `r`；反过来，任何半径为 `r` 的连通核心都必须包含未被前 `r` 层剥离的节点。因此将层数降序排列，第 `k+1` 大层数就是最小答案。

### Python 知识

- `deque` 实现叶子队列，度数减到 1 时入队。
- `sorted(..., reverse=True)[k]` 直接取第 `k+1` 大层数。
- 每个节点只入队一次，代码比二分判定更短。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n log n)`，空间 `O(n)`。

### 总结

连通核心的半径可以从树的外层向内剥离来理解。
