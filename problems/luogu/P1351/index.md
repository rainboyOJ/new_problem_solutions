---
oj: "luogu"
problem_id: "P1351"
title: "[NOIP 2014 提高组] 联合权值"
description: "按中心节点聚合邻居权值，一次得到距离为 2 的有序点对总和与最大值。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["树", "邻居聚合", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1351
---

[[TOC]]

### 题意

统计距离恰好为 2 的有序点对权值乘积的最大值和总和。

### 思路

固定中间点 `u`。它的两个不同邻居形成一个距离 2 的有序点对，因此总和是 `sum^2 - sumsq`，最大值是邻居权值中最大两个数的乘积。

### Python 知识

- 一次扫描维护 `first/second` 两个最大值，不必排序邻居列表。
- `neighbor_sum * neighbor_sum - square_sum` 直接排除相同邻居。
- 正整数权值使最大值初始为 0 足够安全。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n)`，空间 `O(n)`。

### 总结

按距离 2 的中间点分类，树上的二跳计数会变成邻接表上的一次聚合。
