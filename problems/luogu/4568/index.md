---
oj: "luogu"
problem_id: "P4568"
title: "[JLOI2011] 飞行路线"
description: "把免费次数作为分层状态，在 n(k+1) 个状态上运行 Dijkstra。"
difficulty: "提高"
date: 2026-07-17 03:00
toc: true
tags: ["分层图", "Dijkstra", "状态扩展", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4568
---

[[TOC]]

### 题意

无向图中最多让 `k` 条边免费，求起点到终点的最低花费。

### 思路

状态 `(city, used)` 表示已使用 `used` 次免费机会。走一条边既可付费留在本层，也可花一次机会以 0 代价进入下一层；所有新边权仍非负，直接运行 Dijkstra。

### Python 知识

- 二维列表 `distance[used][city]` 对应分层图。
- 堆元组 `(cost, city, used)` 自然按费用排序。
- `min(layer[target] for layer in distance)` 允许免费次数少于 `k`。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(k(n+m)log(kn))`，空间 `O(kn+m)`。

### 总结

“最多使用若干次能力”通常把使用次数加入状态分层。
