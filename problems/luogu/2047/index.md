---
oj: "luogu"
problem_id: "P2047"
title: "[NOI2007] 社交网络"
description: "Floyd 同时维护最短距离和路径数，再按经过节点的路径比例计算重要度。"
difficulty: "提高"
date: 2026-07-17 03:00
toc: true
tags: ["Floyd", "最短路计数", "中心性", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2047
---

[[TOC]]

### 题意

对每个节点，累加所有有序端点对的最短路经过该节点的比例。

### 思路

Floyd 松弛时同时维护 `dist[s][t]` 和最短路条数 `count[s][t]`：更短则覆盖，等长则累加。若 `dist[s][t]=dist[s][v]+dist[v][t]`，经过 `v` 的最短路数是两段条数乘积，据此累加比例。

### Python 知识

- Python 整数自动承载最多 `10^10` 的路径数。
- 二维列表分别保存距离和计数，公式对应清楚。
- `f"{importance:.3f}"` 按要求输出三位小数。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

Floyd 和重要度统计均为 `O(n^3)`，空间 `O(n^2)`。

### 总结

最短路计数与 Floyd 同步更新后，节点经过比例可由两段方案数相乘得到。
