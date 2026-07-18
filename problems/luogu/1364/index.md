---
oj: "luogu"
problem_id: "P1364"
title: "医院设置"
description: "枚举医院节点并在树上 BFS 计算到各点距离，按人口加权后取总和最小值。"
difficulty: "普及/提高-"
date: 2026-07-16 18:17
toc: true
tags: ["树", "BFS", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1364
---

[[TOC]]

### 题意

树上每个节点有居民数。选择一个节点建医院，代价是所有节点人口乘到医院距离之和，求最小代价。

### 思路

`n<=100`，直接枚举医院位置。对每个候选点 BFS 求到全树距离，再计算：

$$
\sum population_i\times distance_i
$$

树中两点路径唯一，BFS 第一次到达的层数就是边数距离。取所有候选代价的最小值即可。

### Python 知识

- 邻接表用列表推导式创建，每条父子边双向加入。
- `map(total_distance,range(1,n+1))` 产生每个候选医院的代价，`min` 直接聚合。
- `deque` 与距离列表完成单源 BFS。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：树也可视为无权图进行 BFS。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：命名函数与 `map/min` 组合。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

deque：

@include-code(./main-pythonic.py, python)

### 复杂度

每个候选 BFS 为 $O(n)$，共 `n` 个候选，总时间 $O(n^2)$，空间 $O(n)$。

### 总结

小规模优化题先考虑直接枚举候选并准确计算代价；树的唯一路径让每次 BFS 很简单。
