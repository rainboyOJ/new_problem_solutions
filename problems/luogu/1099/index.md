---
oj: "luogu"
problem_id: "P1099"
title: "[NOIP 2007 提高组] 树网的核"
description: "先求带权树直径，再用双指针枚举直径上的长度不超过 s 的核心区间。"
difficulty: "提高"
date: 2026-07-17 02:00
toc: true
tags: ["树的直径", "双指针", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1099
---

[[TOC]]

### 题意

在带权树的一条直径上选长度不超过 `s` 的路径，使所有节点到它的最大距离最小。

### 思路

两次树上最远点搜索得到直径端点 `A,B`。对直径节点 `k`，直径外分支深度不会超过它到任一端点的距离；因此区间 `[i,j]` 的偏心距是 `max(dist(A,i), dist(j,B), 最大分支深度)`。直径前缀距离单调，双指针找每个 `i` 能到达的最右 `j`。

### Python 知识

- `for node in order` 可以遍历一个不断 append 的列表，适合非递归树遍历。
- `max(order, key=distance.__getitem__)` 按数组值找最远点。
- 字典 `position` 把直径节点集合变成 `O(1)` 的分支判断。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n)`，空间 `O(n)`。

### 总结

带权树的核问题先降到唯一的直径，再把长度约束转成单调双指针。
