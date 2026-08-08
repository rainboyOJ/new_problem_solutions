---
oj: "luogu"
problem_id: "P6464"
title: "[传智杯 #2 决赛] 传送门"
description: "Floyd 后枚举传送门端点，逐点对比较原路和两个传送方向。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
toc: true
tags: ["Floyd", "枚举", "全源最短路", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P6464
---

[[TOC]]

### 题意

选择两个点安装距离为 0 的双向传送门，最小化所有无序点对最短路之和。

### 思路

先 Floyd 得到原图任意两点距离。固定传送门 `a,b` 后，点对 `x,y` 的新距离是原距离、`x-a-b-y`、`x-b-a-y` 三者最小值；枚举端点和点对求总和。

### Python 知识

- 二维列表直接保存百点规模距离矩阵。
- 内层缓存行引用减少多重索引。
- `min` 接收三个候选，和公式一一对应。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

Floyd `O(n^3)`，枚举约 `O(n^4)`，但 `n<=100`，实际约四分之一点对组合。

### 总结

加一条特殊边后，任意新最短路至多使用一次这条边，可直接枚举两个方向。
