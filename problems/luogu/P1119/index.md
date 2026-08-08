---
oj: "luogu"
problem_id: "P1119"
title: "灾后重建"
description: "按时间增量加入 Floyd 中间点，在线回答当前已重建村庄间最短路。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
toc: true
tags: ["Floyd", "离线询问", "增量算法", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1119
---

[[TOC]]

### 题意

村庄按时间修复，询问某天只经过已修复村庄的最短路。

### 思路

修复时间和询问时间都不下降。维护指针，把修复时间不晚于当前询问的村庄依次作为 Floyd 新中间点；每个中间点只加入一次。端点未修复或距离无穷时输出 -1。

### Python 知识

- 单调询问让一个 `activated` 指针代替每次重新计算。
- 缓存矩阵行引用降低三重循环开销。
- `10**18` 作为整数无穷大，无浮点比较问题。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

总时间 `O(n^3+Q)`，空间 `O(n^2)`。

### 总结

Floyd 的中间点顺序可以与外部时间顺序同步，形成增量全源最短路。
