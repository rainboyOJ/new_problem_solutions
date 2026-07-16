---
oj: "luogu"
problem_id: "P2910"
title: "[USACO08OPEN] Clear And Present Danger S"
description: "Floyd 预处理岛屿两两最短危险值，再累加指定访问序列相邻项。"
difficulty: "普及"
date: 2026-07-17 03:00
toc: true
tags: ["Floyd", "最短路", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2910
---

[[TOC]]

### 题意

必须按给定顺序经过岛屿，求允许经过其他岛屿时的最小总危险值。

### 思路

`n<=100`，用 Floyd 得到任意两岛最短路。序列相邻要求之间彼此独立，答案就是所有 `dist[A_i][A_{i+1}]` 之和。

### Python 知识

- 一次 `read().split()` 配合整数迭代器读取矩阵。
- 缓存 `row`、`through` 减少三重循环索引开销。
- `zip(required, required[1:])` 枚举相邻序列元素。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O(n^3+M)`，空间 `O(n^2)`。

### 总结

访问顺序固定时，先把每一段替换为两点最短路即可独立求和。
